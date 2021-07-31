# control de vaciado para deposito
Control de vaciado para deposito de aguas residuales

Se incluye una carpeta con las versiones de las librerias utilizadas para evitar problemas al compilar.


      ##### NOTAS DE LA VERSION ##### 
      
  * Version 1.1 *

    Cuenta con las funciones de la version 1.0 pero ahora permite modificar la hora del RTC 
    y el MOMENTO de vaciado del deposito usando el pulsador de vaciado MANUAL.

    Nota: 
        Si el momento de vaciado automatico sucede durante el proceso de modificacion
        de datos, dicho evento no pordrá ejecutarse y deberia realizarse de forma manual 
        si no se desea esperar al proximo ciclo diario.

    Para acceder al modo PROGRAMACION  debemos realizad una "doble pulsacion" 
    y se mostrara en pantalla el mensaje: 
                 "CLICK TO SELECT  (Timer/Clock)" 
    Nota: 
        El modo programacion tiene un timeout de 20 segundos, es decir si pasan 20 segundos sin que modifiquemos nada
        el programa vuelve al modo normal de funcionamiento y se anula cualquier cambio parcial.
        Por supuesto, con cada pulsacion el temporizador de control de timeout se resetea permitiendo que
        el proceso de programacion dure todo el tiempo que necesitemos.
    
    Una vez en modo programacion, las "pulsaciones cortas" alternan los mensajes:
      - "PROG >> TIMER  (Empty Moment) "
      - "PROG >> CLOCK    (Modify RTC) "
      
     Mientras se visualiza cualquiera de ellos, una "doble pulsacion" selecciona dicho modo
     y nos lleva hasta el menu de modificacion de valores.
     - En el caso del RTC podemos modificar unicamente hora, minutos y segundos
       No se podrá corregir la fecha. (Pendiente de implementar en futuras versiones)
     
     - En el caso del TIMER solo hora y minuto del momento de inicio de vaciado
       La duracion del proceso de vaciado es de 20 minutos. Establecido en el codigo 
       y no se puede modificar. (Pendiente de implementar en futuras versiones)

     Una vez que estamos en condicion de modificar valores, deberemos hacerlo 'digito a digito':
     El digito que esta activo para ser modificado parpadea con una cadenca de 0.6 segundos
     Inicialmente es el digito situado a la izquierda de la pantalla.
     "Pulsaciones simples" lo incrementan y una vez alcanzado su maximo valor posible, 
     retorna a cero y podreos comenzar de nuevo a incrementarlo.
     (Se ha buscado la manera mas comoda de hacer las cosas partiendo de que solo disponemos de un pulsador)
     
     Para aceptar el valor y cambiar de digito debemos hacer una "doble pulsacion".
     Eel cursor se posicionara en el siguiente digito y comenzara a parpadear de nuevo.
     Asi sucesivametne "doble click" nos ira haciendo avanzar por la cifras para modificarlas 
     o simplemente saltarlas si un determinado digito no necesita ser odificado.
     
     Una vez alcanzado el digito mas a la derecha, si hacemos nuevamente un "doble click" 
     la edicion nos devuelve  al digito mas a la izquierda y asi ciclicamente.

     En cualquier momento una "pulsacion larga" (entre uno y dos segundos) 
     nos permite aceptar los valores modificados y termina el proceso de edicion.
     
     Nota:
        Si se desea cancelar cualquier proceso de edicion, simplemente esperar que se agote el timeout.

     En el caso de que se esten modificando los valores del momento de vaciado del deposito, 
     tras la "pulsacion larga" para aceptar cambios, estos se graban en la memoria EEPROM del microcontrolador
     quedando establecidos como valores por defecto aunque se produzcan cortes de alimentacion del sistema
     o cualquier reinicio accidental.

     Nota:
        Si se cancela la edicion del momento de vaciado no se graba nada en la memoria EEPROM.
     
     Si por algun motivo los datos grabados se corrompen y al iniciarse el sistema no se lee una informacion valida
     correspondiente a una hora y minutos coherentes, el programa utilizará los preprogramados en el codigo, 
     es decir la hora de vaciado quedará establecida por defecto a las 20:00.

     Nota: 
        Durante la edicion tanto del RTC como del TIMER el programa comprobará 
        la coherencia de los datos que se van modificando, de modo que no podremos escribir 
        una hora que sea mayor de 23 o un minuto mayor a 59.

        
 ===================
  ** Version 1.0 **
 ===================
    Sistema de vaciado de depposito de aguas residuales a una hora programa.
    El control de tiempo se realiza con un RTC DS3231
    El sistema utiliza tiempos preestablecidos y no pueden ser modificados (en esta vession)
    La hora por defecto de vaciado del deposito es a las 20:00.
     - En su modo AUTOMATICO el deposito abre su valvula a la hora incicada 
       y la mantiene abierta durante 20 minutos que es el tiempo estimado 
       para el vaciado completo del deposito.
   
     - Se dispone tambien de un pulsador para vaciado MANUAL.
       Para activar el proceso de vaciado manualmente debemos realizar una "pulsacion larga" (entre 1 y 2 segundos)
       Ello desencadena el proceso de vaciado que se prolongará durante los 20 mitutos preestablecios por el sistema
       Si se desea interrumpir el proceso de vaciado será posible hacerlo mediante una nueva "pulsacion larga".

     Nota: 
        La interrupcion del proceso será posible tanto si esta se ha iniciado de forma programada o manualmente.
        durante el proceso de vaciado se visualizará en pantalla una cuenta atras 
        con el tiempo que resta de proceso, al tiempo que parpadeará el mensaje  " EMPTYING TANK  " 
        y el led Onboard de la placa (salida D13) permanecerá encendido.
        
        Durante los procesos de apertura y cierre de la valvula se mostraran parpadeando en pantalla los mensajes
        " OPENING... " y " CLOSING...  " respectivamente y el led Onboard de la placa (salida D13) parpadeará.

    La luz del display se apaga unos segundos despues de iniciarse el sistema.
    Durante la apertura de valvula, proceso de vaciado y cierre de valvula, el LCD permaneceré encendido.
    Durante el tiempo de espera hasta un nuevo ciclo de vaciado, el display permanecerá apagado, 
    salvo que el usuario interactue por pedio del pulsador en cuyo caso semantendra encendida 
    durante TIMEOUT segundos.
    Por tanto si se desea encender la luz del LCD para visualizar mejor la pantalla sin provocar 
    el vaciado manual, debemos usar una "pulsacion corta".

*/
