REF:
http://beej-zhtw.netdpi.net/07-advanced-technology/7-2-select
http://objectaline19.blogspot.com/2017/03/linux-file-locking.html
https://blog.csdn.net/zqy2000zqy/article/details/1137905
http://beej-zhtw.netdpi.net/09-man-manual/9-19-select?tmpl=%2Fsystem%2Fapp%2Ftemplates%2Fprint%2F&showPrintDialog=1

Discuss with:
B07902047 羅啟帆
B07902001 徐維謙

一開始先把讀/寫資料的部份搞定，接下來弄multiplexing的部份，最後則是上lock
讀寫資料的時候遇到最大的問題就是還沒有很了解整個socket是怎麼運作的，所以在處理write_sever分兩行輸入的時候花了許多時間了解
multiplexing的部份則是在參考資料與try & error的過程中慢慢摸出select的用法
最後的lock屬於比較簡單的部份，唯一遇到比較困難的bug則是忘記close函式只能在最後的時候call，不然在中途call就會不小心把所有lock都提早release掉。
