# OTUS Home Work 2.
1. Introducing ip_filter that works with respect to the HW requirements in
   https://otusmetodist.yonote.ru/share/2cb07ace-75b1-48fe-b6fd-259b39f6025a/doc/2-filtraciya-ip-adresov-s8zT8mUKCH
2. Implements build-system as in the first HomeWork.

## How Ip Filter works
1) Get strings from the input
2) Each string should contain ip address in the format of [xxx.xxx.xxx.xxx]
Expected string is the [text1 \t text2 \t text3 \n], where text2 and text3 fields are ignored.
text 1 contains ip address itself. 
3) If input data is correct, ip addresses then sorted in reverse-lexicography order.
4) Then full list of sorted addresses is output to stdout in format "one string-one address"
5) Then all addresses with the first byte of which equals "1". Order is the same as previous one
6) Then all addresses with the first byte equals "46" and second one equals "70". Order is the same as previous one
7) Then all addresses which has any byte equals "46". Order is the same as previous one
 

## How To
1) Command cat ip_filter.tsv | ip_filter | md5sum
Really gives
24e7a7b2270daee89c64d3ca5fb3da1a -
2) GTest also check it. See TEST(CinTest, ReadInputFromFile)


