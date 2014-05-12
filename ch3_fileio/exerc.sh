
# strace -f -o st /bin/bash
# ls  / asd 2>&1 > ou

20469 dup2(1, 2)                        = 2
20469 fcntl(1, F_GETFD)                 = 0

20469 open("ou", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
20469 dup2(3, 1)                        = 1
20469 close(3)                          = 0

20469 execve("/bin/ls", ["ls", "--color=auto", "/", "asd"], [/* 15 vars */]) = 0

# strace -f -o st /bin/bash
# ls  / asd > ou 2>&1 

21273 open("ou", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
21273 dup2(3, 1)                        = 1
21273 close(3)                          = 0

21273 dup2(1, 2)                        = 2
21273 fcntl(1, F_GETFD)                 = 0

21273 execve("/bin/ls", ["ls", "--color=auto", "/", "asd"], [/* 15 vars */]) = 0