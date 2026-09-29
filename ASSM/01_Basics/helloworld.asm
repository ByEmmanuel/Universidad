bits 64
global _start

section .data

  msg db "Hola mundo! :)", 0Ah
  longitud equ $ - msg

section .text
_start:
  ; 1 imprimir el mensaje (sys_write) 
  mov rax, 1 ; codigo de sys_write para linux
  mov rdi, 1 ; destino 1 = la pantalla
  mov rsi, msg ; usamos 64 bits para la direccion del texto
  mov rdx, longitud ; usamos rdx 64 bits para la cantidad de letras
  syscall ; llamamos al kernel de linux

  ; 2. terminar el progama correctamente (sys_exit)
  mov rax, 60 ; codigo de sys_exit para linux
  mov rdi, 0 ; codigo de salida 0 (sin errores) 
  syscall ; llamamos al kernel de linux para cerrar
