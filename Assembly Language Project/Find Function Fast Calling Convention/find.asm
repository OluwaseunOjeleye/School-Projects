SECTION .DATA

SECTION .TEXT
    GLOBAL find
    
find: 
    xchg rsi, rdi

    mov r10, rsi
    mov r11, rdi

    mov rdi, rsi
    call strlen
    mov r12, rdx    ;len1

    mov rdi, r11
    call strlen
    mov r13, rdx    ;len2

    mov rsi, r10
    mov rdi, r11

    call Clear

    mov r11, r12
    sub r11, r13
    add r11, 1


    cmp r12, r13
    jl NOTFOUND
    je Samelength

    call Find
    ret 

strlen:
    sub rcx, rcx
    sub al, al
    not rcx
    cld
    repne   scasb
    not rcx
    dec rcx
    mov rdx, rcx
    jmp EXIT

Samelength:
    cld
    repe cmpsb
    jne NOTFOUND

    mov r10, 1
    jmp FOUND

Find:
    inc r10
    cmp r10, r11
    jg NOTFOUND
    
    mov r8, -1
    jmp Compare_Blk

Check: 
    cmp r8, r13
    je FOUND
    
    jmp Find

Compare_Blk:
    inc r8
    cmp r8, r13
    jl Compare
    
    jmp Check
    
Compare:
    mov r9, r8
    add r9, r10
    sub r9, 1
                
    mov rcx, rsi            
    mov rdx, rdi
    
    add rcx, r9
    add rdx, r8
    
    mov al, [rcx]
    mov ah, [rdx]
    
    cmp al, ah
    je Compare_Blk
    
    jmp Check

FOUND:
    sub r10, 1
    mov rax, r10
    jmp EXIT

NOTFOUND:
    mov rax, -1  
    jmp EXIT  

Clear:
    mov r10, 0
    mov r11, 0
    mov rcx, 0
    mov rdx, 0
    mov al, 0
    cld
    jmp EXIT
  
EXIT:       
    RET