# ๐จ How To Build the file with Makefile
Build๋ฅผ ํ๊ธฐ ์ํด์๋ ๋ฏธ๋ฆฌ ์์ฑํ Makefile์ ์คํํ๋ ๋ค์ ๋ช๋ น์ด๋ฅผ ์คํํ๋ฉด ๋๋ค.  
๋ค์ ๋ช๋ น์ด๋ฅผ ์ํํ๊ฒ ๋๋ฉด test์ test2 ํ์ผ ์ด 2๊ฐ๊ฐ ์์ฑ๋๋ค.  
testํ์ผ์ part1๋ง testํ๋ ํ์ผ์ด๋ฉฐ, test2ํ์ผ์ part1๊ณผ part2๋ฅผ ๋ชจ๋ testํ  ์ ์๋ ํ์ผ์ด๋ค.  
test์ test2 ํ์ผ์ ๊ธฐ๋ณธ์ ์ผ๋ก ๊ตฌ์กฐ๋ ๊ฐ์ผ๋ฉฐ, test2์์๋ ์ฃผ๊ธฐ์ ์ผ๋ก ํ์ผ์ scanํ๊ธฐ ์ํ  
timer๋ฅผ ํธ์ถํ๋ system call์ ๋ถ๋ฅธ๋ค.  

```$ make```

<br/>

# โ How To Execute file
์์ฑ๋ test ์คํํ์ผ์ ์คํํ๊ธฐ ์ํ ๋ช๋ น์ด๋ ๋ค์๊ณผ ๊ฐ๋ค.  
<test์ ๊ฒฝ์ฐ>

```$ ./test```  

<test2์ ๊ฒฝ์ฐ>  
```$ ./test2```  

์ด๋, test2์ ๊ฒฝ์ฐ์ page๋ฅผ scanํ์ฌ struct page์ ์๋ก ์ถ๊ฐํ counter ๋ณ์์ ์ ๊ทผํ๊ธฐ ๋๋ฌธ์,  
์์ ๋ kernel source๋ฅผ bootํ ํ ์คํํด์ผ ์ ์์ ์ผ๋ก ๋์ํ๋ค.   

# How To Build My Kernel  
kernel.diff ํ์ผ์ ์ฌ์ฉํ  ์ ์๋ค.  

workspace/sce394-linux-kernel-labs/kernel-utils/src/linux-5.15.4 ํด๋ ๋ด์  
kernel.diff๋ฅผ ๋ถ์ฌ๋ฃ๊ธฐ ํ ํ, ๋ค์ ๋ช๋ น์ด๋ฅผ ์๋ ฅํ๋ค.  
```patch -p1 < /kernel.patch```  

์ดํ, workspace/sce394-linux-kernel-labs/kernel-utils ํด๋ ๋ด์์  
```./boot linux-5.15.4``` ๋ฅผ ์๋ ฅํ๋ฉด kernel์ด boot๋๋ค.  