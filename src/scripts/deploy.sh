#!/bin/bash

[ -z "$(command -v realpath)" ] && printf "%s\n" "ERROR: realpath utility must be installed!" && exit 1
[ -z "$(command -v jq)" ] && printf "%s\n" "ERROR: jq utility must be installed!" && exit 1
[ -z "$(command -v dpkg-deb)" ] && printf "%s\n" "ERROR: dpkg-deb not found!" && exit 1

HW2_BINARY_DIR="$(pwd)"

HW2_CONFIGURE_ARGUMENTS=
HW2_MAKE_ARGUMENTS=
HW2_BUILD_TOOL="make"

HW2_BUILD_NUMBER=0
CHECK_NINJA_INSTALLATION=0

BUILD_DIR="${HW2_BINARY_DIR}"/build
BUILD_TYPE=Debug
PRODUCTION_BUILD=0
HW2_DEFAULT_INSTALL_PREFIX="${HW2_BINARY_DIR}"/install
HW2_INSTALL_PREFIX=${HW2_DEFAULT_INSTALL_PREFIX}

VERSION_FILE="${HW2_BINARY_DIR}"/src/versioning/Version.json

# PACKAGE_NAME_PREFIX hardcoded due to Home Work requirements
PACKAGE_NAME_PREFIX=ipfilter-uvarenkov
PACKAGE_BUILD_DIR="${BUILD_DIR}"/package_build
PACKAGE_VERSION=0.0.0
PACKAGE_CONTROL_FILE="${HW2_BINARY_DIR}"/src/package/control.json
MAIN_TARGET_EXECUTABLE_NAME=ip_filter
BOOST_TESTS_EXEC_NAME=ip_filter_boost_tests


create_package_control_file()
{
	touch control
	{
		echo "Package: ${PACKAGE_NAME}"
		echo "Architecture: $(jq -r '.architecture' "${PACKAGE_CONTROL_FILE}")"
		echo "Maintainer: $(jq -r '.maintainer' "${PACKAGE_CONTROL_FILE}")"
		echo "Priority: $(jq -r '.priority' "${PACKAGE_CONTROL_FILE}")"
		echo "Version: ${PACKAGE_VERSION}"
		echo "Description: $(jq -r '.description' "${PACKAGE_CONTROL_FILE}")"
	} >> control

}

create_and_install_package()
{
	mkdir -p "${PACKAGE_BUILD_DIR}" || exit 1
	pushd "${PACKAGE_BUILD_DIR}" || exit 1

	PACKAGE_NAME="${PACKAGE_NAME_PREFIX}"-"${PACKAGE_VERSION}"
	mkdir -p "${PACKAGE_NAME}"/DEBIAN
	pushd "${PACKAGE_NAME}"/DEBIAN || exit 1
	create_package_control_file

	popd || exit 1
	mkdir -p "${PACKAGE_NAME}"/usr/bin

	cp "${HW2_INSTALL_PREFIX}"/${MAIN_TARGET_EXECUTABLE_NAME} "${PACKAGE_NAME}"/usr/bin

	dpkg-deb --build "${PACKAGE_NAME}" || exit 1

	cp "${PACKAGE_NAME}".deb "${HW2_INSTALL_PREFIX}"

	popd || exit 1

}



error()
{
	printf "%s\n" "[ERROR]: $*"
	exit 1
}

try()
{
	if ! "$@"; then
		error "$* failed"
	fi
}

process_option()
{
	case $1 in

	--install-to=*)
		try mkdir -p "${1#--install-to=}"
		HW2_INSTALL_PREFIX="$(realpath "${1#--install-to=}")"
	;;

	--build-number=*)
		HW2_BUILD_NUMBER=${1#--build-number=}
	;;

	--skip-configuration)
		SKIP_HW2_CONFIGURATION=true
	;;

	--ninja)
		CHECK_NINJA_INSTALLATION=1
		HW2_BUILD_TOOL=ninja
	;;

	--production)
		BUILD_TYPE=MinSizeRel
		PRODUCTION_BUILD=1
	;;

	-D*)
		HW2_CONFIGURE_ARGUMENTS+=" $1"
	;;

	-*)
		HW2_MAKE_ARGUMENTS+=" $1"
	;;

	*)
		printf "%s\n" "ERROR: unknown option $1"
		exit 1
	;;

	esac
}

clean_build_dir()
{
	try rm -rf "${BUILD_DIR}"
}

configure()
{

	printf "%s\n" "[CONFIG] Arguments: [${HW2_CONFIGURE_ARGUMENTS}] "

	if [ ${PRODUCTION_BUILD} -gt 0 ]; then
		printf "%s\n" "[CONFIG] Configuring for production"
	fi

	CMAKE_CMD+="-DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
	CMAKE_CMD+="${HW2_CONFIGURE_ARGUMENTS}"
	CMAKE_CMD+=" -DHW2_INSTALL_PREFIX:PATH=${HW2_INSTALL_PREFIX}"
	CMAKE_CMD+=" -DHW2_PROJECT_VERSION_MAJOR:STRING=${PROJECT_VERSION_MAJOR}"
	CMAKE_CMD+=" -DHW2_PROJECT_VERSION_MINOR:STRING=${PROJECT_VERSION_MINOR}"
	CMAKE_CMD+=" -DMAIN_TARGET_EXECUTABLE_NAME:STRING=${MAIN_TARGET_EXECUTABLE_NAME}"
	CMAKE_CMD+=" -DBOOST_TESTS_EXEC_NAME:STRING=${BOOST_TESTS_EXEC_NAME}"


	printf "%s\n" "BUILD NUMBER: ${HW2_BUILD_NUMBER}"

	if [ -n "${HW2_BUILD_NUMBER}" ]; then
		PROJECT_VERSION_BUILD=${HW2_BUILD_NUMBER}
		PACKAGE_VERSION=${PACKAGE_VERSION}.${HW2_BUILD_NUMBER}
	else
		PACKAGE_VERSION=${PACKAGE_VERSION}.0
	fi

	export PACKAGE_VERSION=${PACKAGE_VERSION}
	if [ -n "$GITHUB_ACTIONS" ]
  then
       echo "PACKAGE_VERSION=${PACKAGE_VERSION}" >> "${GITHUB_ENV}"
  fi


	CMAKE_CMD+=" -DHW2_PROJECT_VERSION_BUILD:STRING=${PROJECT_VERSION_BUILD}"

	CMAKE_CMD+=" -S ${HW2_BINARY_DIR}"
	CMAKE_CMD+=" -B ${BUILD_DIR}"
	printf "%s\n" "[CONFIG] CMAKE_ARGS: ${CMAKE_CMD}"

	#This is intended approach.
	# shellcheck disable=SC2086
	cmake ${CMAKE_CMD}

}

build_project()
{
	pushd "${BUILD_DIR}" || exit 1

	"${HW2_BUILD_TOOL}" install

	popd || exit 1
}

get_version()
{
	PROJECT_VERSION_MAJOR="$(jq '.major' "${VERSION_FILE}")"
	PROJECT_VERSION_MINOR="$(jq '.minor' "${VERSION_FILE}")"
	PROJECT_VERSION_BUILD=$(jq '.build' "${VERSION_FILE}")

	PACKAGE_VERSION="${PROJECT_VERSION_MAJOR}"."${PROJECT_VERSION_MINOR}"
}

args=( "$@" )
printf "[INIT] Deploy arguments: [ "
printf "%s " "${args[@]}"
printf " ]\n"


for ARGUMENT in "${args[@]}"; do
	NONASCII=$(printf "%s\n" "$ARGUMENT" | perl -pe 's/[[:ascii:]]//g;')
	if [ -n "$NONASCII" ]; then
		printf "%s\n" "ERROR: Non-ASCII symbol in parameter: ${ARGUMENT}. Pass only ASCII letters from a terminal."
		exit 1
	fi
done

for ARGUMENT in "${args[@]}"; do
	printf "%s\n" "Processing ${ARGUMENT}..."
	process_option "$ARGUMENT"
done

if [ ${CHECK_NINJA_INSTALLATION} -gt 0 ]; then

		if [ -n "$(command -v ninja 2>/dev/null)" ]; then
			HW2_CONFIGURE_ARGUMENTS+=" -G Ninja"
		else
			error "Install ninja first"
		fi

fi

get_version

if [ -z "${SKIP_HW2_CONFIGURATION}" ]; then

	clean_build_dir
	configure

fi

build_project
create_and_install_package