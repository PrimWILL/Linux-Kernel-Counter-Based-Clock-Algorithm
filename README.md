# 🔨 How To Build the file with Makefile
Build를 하기 위해서는 미리 작성한 Makefile을 실행하는 다음 명령어를 실행하면 된다.  
다음 명령어를 수행하게 되면 test와 test2 파일 총 2개가 생성된다.  
test파일은 part1만 test하는 파일이며, test2파일은 part1과 part2를 모두 test할 수 있는 파일이다.  
test와 test2 파일은 기본적으로 구조는 같으며, test2에서는 주기적으로 파일을 scan하기 위한  
timer를 호출하는 system call을 부른다.  

```$ make```

<br/>

# ⚙ How To Execute file
생성된 test 실행파일을 실행하기 위한 명령어는 다음과 같다.  
<test의 경우>

```$ ./test```  

<test2의 경우>  
```$ ./test2```  

이때, test2의 경우에 page를 scan하여 struct page에 새로 추가한 counter 변수에 접근하기 때문에,  
수정된 kernel source를 boot한 후 실행해야 정상적으로 동작한다.   

# How To Build My Kernel  
kernel.diff 파일을 사용할 수 있다.  

workspace/sce394-linux-kernel-labs/kernel-utils/src/linux-5.15.4 폴더 내에  
kernel.diff를 붙여넣기 한 후, 다음 명령어를 입력한다.  
```patch -p1 < /kernel.patch```  

이후, workspace/sce394-linux-kernel-labs/kernel-utils 폴더 내에서  
```./boot linux-5.15.4``` 를 입력하면 kernel이 boot된다.  