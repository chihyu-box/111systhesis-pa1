0. wget https://github.com/berkeley-abc/abc/archive/refs/heads/master.zip
   unzip master.zip

1. 把task1裡的Makefile覆蓋到abc-master目錄下

2. 把task1裡的pa1資料夾複製到abc-master/src目錄下

3. 把task1裡的mainInit.c覆蓋到abc-master/src/base/main目錄下

4. 在abc-master目錄下 輸入make && make libabc.a

註* 如果先前已經編譯過 會出現沒辦法使用的情況 不太知道原因在哪裡 如果是乾淨未編譯過的就可以

5. 待編譯完成後，輸入./abc

6. 輸入 read [inputfile] ex. read i10.aig

7. 輸入 strash

8. 輸入 iteratentk
