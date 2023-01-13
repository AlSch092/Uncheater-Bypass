.data
lpGetWindowReturn dq 0
lpPostMessageWReturn dq 0
lpGetClassNameWReturn dq 0
lpGetModuleHandleWReturn dq 0
lpOpenProcessReturn dq 0
lpGetVolumeInformationW dq 0
lpSetSendBufferReturn dq 0
lpSetSendBufferCallback dq 0 ;callbacks are our C/C++ functions that we can call through here

lpSendPacket dq 0

lpSetPositionReturn dq 0
lpPlayerPositionCallback dq 0

lpClientDebugLogReturn dq 0
lpClientDebugLogCallback dq 0

.code

GetModuleHandleWHook_Init PROC
	mov lpGetModuleHandleWReturn, rcx
	ret
GetModuleHandleWHook_Init ENDP

GetModuleHandleWHook PROC

	pop r10 ;neccessary stack cleanup from hook jump

	xor rcx,rcx
Default:
	mov [rsp+10h],rbx
	jmp lpGetModuleHandleWReturn
GetModuleHandleWHook ENDP

GetWindowHook_Init PROC
	mov lpGetWindowReturn, rcx
	ret
GetWindowHook_Init ENDP

GetWindowHook PROC ;third param - use return address?

	pop r10 ;neccessary stack cleanup from hook jump

	cmp rdx, 5

	je ChildWindow
	jmp Default

ChildWindow:
	mov rdx, 1
Default:
	mov [rsp+08],rbx
	jmp lpGetWindowReturn

GetWindowHook ENDP

PostMessageWHook_Init PROC
	mov lpPostMessageWReturn, rcx
	ret
PostMessageWHook_Init ENDP

PostMessageWHook PROC

	pop r10 ;neccessary stack cleanup from hook jump

	cmp rdx, 112h  ;close window
	je closeWindow
	jmp Default
	
closeWindow:
	mov rdx, 0
	mov r8, 0

Default:
	mov [rsp+10h], rbx
	jmp lpPostMessageWReturn

PostMessageWHook ENDP


GetClassNameWHook_Init PROC
	mov lpGetClassNameWReturn, rcx
	ret
GetClassNameWHook_Init ENDP

GetClassNameWHook PROC

	pop r10 ;neccessary stack cleanup from hook jump

	xor r8, r8
	xor rcx,rcx
	xor r10,r10 ;restore 

	sub rsp,38h
	jmp lpGetClassNameWReturn

GetClassNameWHook ENDP

OpenProcessHook_Init PROC
	mov lpOpenProcessReturn, rcx
	ret 
OpenProcessHook_Init ENDP

OpenProcessHook PROC

	pop r10 ;neccessary stack cleanup from hook jump

	xor r8,r8
Default:
	mov r11, rsp
	sub rsp, 68h
	jmp lpOpenProcessReturn
OpenProcessHook ENDP

GetVolumeInformationWHook PROC
	
	pop r10 ;neccessary stack cleanup from hook jump

	mov r8, 0 ;0 bytes size
	
	mov rax,rsp
	mov [rax+8],rbx
	jmp lpGetVolumeInformationW
GetVolumeInformationWHook ENDP

GetVolumeInformationWHook_Init PROC
	mov lpGetVolumeInformationW, rcx
	ret
GetVolumeInformationWHook_Init ENDP


SetSendBuffer_HookInitialize PROC
	mov lpSetSendBufferReturn, rcx
	mov lpSetSendBufferCallback, rdx
	ret
SetSendBuffer_HookInitialize ENDP

SetSendBuffer_Hook PROC

  ;removed from public source
  ;this games send packet stuff is actually difficult to solve! good luck, I found it easier to emulate the entire encryption scheme than calling the in-game method
  
	jmp lpSetSendBufferReturn
SetSendBuffer_Hook ENDP

SetPositionHook_Init PROC
	mov lpSetPositionReturn,rcx
	mov lpPlayerPositionCallback, rdx
	ret
SetPositionHook_Init ENDP

PlayerPosition_Hook PROC

    pop r10

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    pushfq

    sub rsp, 1028h

    ;RCX = Vec3
    mov rcx, rsi
    call lpPlayerPositionCallback 

    add rsp, 1028h

    popfq
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    movups xmm1, [rsi+200h] ;rsi+200 = BONE Vec3 structure, to move the character you need to move the correct BONE list entry. the game also checks if you're teleporting and logs you to their 'cheat' database
    jmp lpSetPositionReturn

PlayerPosition_Hook ENDP

ClientDebugLog_Init PROC
    mov lpClientDebugLogReturn, rcx
    mov lpClientDebugLogCallback, rdx 
    ret
ClientDebugLog_Init ENDP

ClientDebugLog_Hook PROC

    pop r10

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    pushfq

    sub rsp, 1028h
    mov rcx, rax
    call lpClientDebugLogCallback 

    add rsp, 1028h

    popfq
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax


    pop r15 ;original bytes
    pop r14
    pop r12
    jmp lpClientDebugLogReturn

ClientDebugLog_Hook ENDP

END
