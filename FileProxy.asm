.data
lpXAudio2Create dq 0
lpCreateAudioReverb dq 0
lpCreateAudioVolumeMeter dq 0
lpX3DAudioInitialize dq 0
lpInitialize_X3DAudioCalculate dq 0
lpCreateFX dq 0

lpInitializeAddresses dq 0

.code

;jump funcs

PUBLIC XAudio2Create

XAudio2Create PROC
	jmp lpXAudio2Create
XAudio2Create ENDP

CreateAudioReverb PROC

	jmp lpCreateAudioReverb
CreateAudioReverb ENDP

CreateAudioVolumeMeter PROC
	jmp lpCreateAudioVolumeMeter
CreateAudioVolumeMeter ENDP

CreateFX PROC
	jmp lpCreateFX
CreateFX ENDP

X3DAudioCalculate PROC
	jmp lpInitialize_X3DAudioCalculate
X3DAudioCalculate ENDP

X3DAudioInitialize PROC
	jmp lpX3DAudioInitialize
X3DAudioInitialize ENDP

;initializer funcs

Initialize_CreateAudioReverb PROC
	mov lpCreateAudioReverb, rcx
	ret
Initialize_CreateAudioReverb ENDP

Initialize_CreateAudioVolumeMeter PROC
	mov lpCreateAudioVolumeMeter, rcx
	ret
Initialize_CreateAudioVolumeMeter ENDP

Initialize_XAudio2Create PROC
	mov lpXAudio2Create, rcx
	ret
Initialize_XAudio2Create ENDP

Initialize_X3DAudioInitialize PROC
	mov lpX3DAudioInitialize, rcx
	ret
Initialize_X3DAudioInitialize ENDP

Initialize_X3DAudioCalculate PROC
	mov lpInitialize_X3DAudioCalculate, rcx
	ret
Initialize_X3DAudioCalculate ENDP

Initialize_CreateFX PROC
	mov lpCreateFX, rcx
	ret
Initialize_CreateFX ENDP

END
