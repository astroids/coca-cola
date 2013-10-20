.code 
;void adjustASM(unsigned char* norm,	rcx
;			unsigned char * ori,		rdx
;			 short bar, 				r8w
;			INT32 size);				r9d
;
;
adjustASM proc
	mov r10,0			;offset =0
	cmp r8w,0			;+- mi	sadece son byti dolu
	jl decrease			;azaltiyosa asaya atla yoksa dvm
	mov r11w , 0ffffh   ;11111111111		//cmov bytta ise yaramiyo
	
mainadd:
	mov al , byte ptr [rdx+r10]; ilk bayti memoriden al
	add al, r8b				   ; br arttir
	cmovc  ax,r11w 				;conditional move carry, ustte carry varsa 
								;yani 255i geciyorsa 11111 yap al yi cmov bytta calismiyo

	mov byte ptr [rcx +r10], al; aldigini geri koy
	inc r10 ;	i++
	dec r9d ;  image size 0 oluncaya kadar loop
	jnz	mainadd
	
	
decrease:
	mov r11w,0;
	neg r8w
mainsub:
	mov al , byte ptr [rdx+r10]; ilk bayti memoriden al
	sub al, r8b				   ; br azalt
	cmovc  ax,r11w 				;conditional move carry, ustte carry varsa 
								;yani 255i geciyorsa 11111 yap al yi cmov bytta calismiyo

	mov byte ptr [rcx +r10], al; aldigini geri koy
	inc r10 ;	i++
	dec r9d ;  image size 0 oluncaya kadar loop
	jnz	mainsub
	
	
	
	ret
adjustASM endp
		end