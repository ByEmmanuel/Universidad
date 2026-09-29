global _start ;  le dice al SO donde empezar 

section .text ; en esta seccion va el codigo que queremos ejecutar / realizar
_start:
    ; hacemos nuesta operacion matematica
    mov ax, 5 ; colocamos un 5 en el registro rax
    add ax, 3 ; le sumamos 3 al registro rax 

    ; ahora preparamos la salida del programa (sys_exit)
    mov di, ax ; movemos el registro rax al registro rdi
                 ; linux usa rdi para leer el codigo de salida
    
    mov ax, 60  ; colocam os 60 en rax. (60 es el codigo para sys_exit)
    syscall      ; Interrumpimos el programa y le pasamos el control al kernel de linux
