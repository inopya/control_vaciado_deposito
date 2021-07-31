/*
#       _\|/_   A ver..., ¿que tenemos por aqui?
#       (O-O)        
# ---oOO-(_)-OOo---------------------------------
 
 
##########################################################
# ****************************************************** #
# *           DOMOTICA PARA PRINCIPIANTES              * #
# *         CONTROL DE VACIADO DE DEPOSITO             * #
# *          Autor:  Eulogio López Cayuela             * #
# *                                                    * #
# *       Versión 1.1       Fecha: 06/06/2020          * #
# ****************************************************** #
##########################################################
*/

#define __VERSION__ "CONTROL DE VACIADO DE DEPOSITO v1.1"


/*
      ##### NOTAS DE LA VERSION ##### 
      
 ===================
  ** Version 1.1 **
 ===================

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

    NOTA ACLARATORIA:
    
      Es verdad quese se podia haber facilitado el uso de los modos de programacion de RTC y TIMER 
      añadiendo mas pulsadores, cosa que no hubiese sido un problema dado que hay suficiente 
      disponibilidad de Entradas/Salidas, pero este montaje reponde y resuelve una duda planteada 
      sobre un caso real en el que las condiciones y distribucion fisica son las mostradas en el esquema.
      Sirva asi mismo como ejemplo de aplicacion practica de la libreria para control de eventos en pulsadores:
      https://github.com/inopya/inopya_ClickButton_v2_pullup

    USO DEL PULSADOR (segun el estado del programa en que nos encontremos).
    ** MQ_WAIT:
      - 1 pulsacion simple:   enciende la luz del LCD
      - 1 pulsacion larga:    inicia el proceso de vaciado
      - 1 pulsacion doble:    nos lleva al menu de seleccion para modificar RTC/TIMER
                              (pulsacione simples en ese menu selecciona ciclicamente una u otra opcion)
                              (unaboble pulscion selecciona el modo que este visualizado en pantalla)
     ** MQ_PROG_MODE: 
      - 1 pulsacion simple:   incrementan el digito seleccionado
      - 1 pulsacion doble:    mueven el cursor al siguiente digito
      - 1 pulsacion larga:    acepta os cambios y sale de edicion

    ** MQ_EMPTIYING:
      - 1 pulsacion larga:   interrumpe el proceso de vaciado
        

*/



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCIONPARA IMPORTACION DE LIBRERIAS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#include <Wire.h>  
#include <RTClib.h>  
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>        // https://gitlab.com/tandembyte/LCD_I2C

#include <Temporizador_inopya.h>      // https://github.com/inopya/Temporizador_Virtual
                                      // gestion de temporiadores de forma sencilla y "amigable"
                                      
#include <ClickButton.h>              // https://github.com/inopya/inopya_ClickButton_v2_pullup
                                      // gestion simplificada de deteccion de eventos en pulsadores





/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        ALGUNAS DEFINICIONES PERSONALES PARA MI COMODIDAD AL ESCRIBIR CODIGO
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#define AND          &&
#define OR          ||
#define NOT          !
#define ANDbit       &
#define ORbit        |
#define XORbit       ^
#define NOTbit       ~

#define getBit(data,y)       ((data>>y) & 1)           // Obtener el valor  del bit (data.y)
#define setBit(data,y)       data |= (1 << y)          // Poner a 1 el bit (data.y) 
#define clearBit(data,y)     data &= ~(1 << y)         // Poner a 0 el bit (data.y)
#define togleBit(data,y)     data ^= (1 << y)          // Invertir el valor del bit (data.y)
#define togleByte(data)      data = ~data              // Invertir el valor del byte (data)

#define SERIAL_BEGIN        Serial.begin
#define SERIAL_END          Serial.end
#define PRINT               Serial.print
#define PRINTLN             Serial.println
#define PRINT_DEBUG         //Serial.print
#define PRINTLN_DEBUG       //Serial.println
#define SERIAL_BAUD_RATE    115200


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DEFINICION DE PINES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#define PIN_RELE_OPEN         12      // Rele para apertura de valvula.
#define PIN_RELE_CLOSE        11      // Rele para cierre de valvula.
#define PIN_PULSADOR           2      // permite actuar en modo manual y programar


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DEFINICION DE CONSTANTES DEL PROGRAMA
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

#define LED_ONBOARD           13      // LED integrado en las placas tipo "Arduino".

#define ON                   LOW      // Reles se activan a nive bajo
#define OFF                 HIGH 
#define TIMEOUT               8

   

/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE DEFINICION DE VARIABLES GLOBALES
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/


/* ENUM ESTADOS MAQUINA */
enum estados_maquina
{
  MQ_START            =   0,    //  inicio tras recibir corriente  
  MQ_WAITING          =  20,    //  inicio de vaciado, abriendo
  MQ_BEGIN_TASK       =  21,    //  inicio de vaciado, abriendo
  MQ_OPENNIG          =  22,    //  inicio de vaciado, abriendo
  MQ_EMPTYING         =  23,    //  vaciando deposito
  MQ_CLOSING          =  24,    //  fin de vaciado, cerrando

  MQ_PROG_MODE        =  30,
  MQ_PROG_TIMER       =  31,
  MQ_PROG_CLOCK       =  32, 
  MQ_TEST ,                     //  modo test, sin uso
};

/* POSICINES CURSOR - EDICION RTC - HORA */
enum enumPosicionesCursorHora 
{
  CUR_HORA1   =   4,    //
  CUR_HORA2   =   5,    //
  CUR_MINU1   =   7,    //
  CUR_MINU2   =   8,    //
  CUR_SEGU1   =  10,    //
  CUR_SEGU2   =  11,    // 
};

/* POSICINES CURSOR - EDICION RTC _FECHA (sin uso) */
enum enumPosicionesCursorFecha 
{
  CUR_DIA1   =   3,    // 
  CUR_DIA2   =   4,    // 
  CUR_MES1   =   6,    //
  CUR_MES2   =   7,    //
  CUR_ANO1   =  11,    //
  CUR_ANO2   =  12,    //
};

/* POSICINES CURSOR - EDICION TIMER VACIADO */
enum enumPosicionesCursorVaciado 
{
  CUR_VAC_HORA1   =   5,    //
  CUR_VAC_HORA2   =   6,    //
  CUR_VAC_MINU1   =   8,    //
  CUR_VAC_MINU2   =   9,   //
};

/* TIPOS DE PULSACION - Libreria inopya */
enum enumTiposPulsacion 
{
  PULSACION_NULA        =   0,    //
  PULSACION_CORTA       =   1,    //
  PULSACION_DOBLE       =   2,    //
  PULSACION_LARGA       =   3,    //
  PULSACION_SOSTENIDA   =   9,    //
};



uint8_t estado_actual = 0;
uint8_t horas;
uint8_t minutos;
uint8_t segundos;
uint8_t segundos_anterior=101;  //inicializado fuera de rango

uint32_t momento_proximo_evento;
int valor_cuenta_atras = 0;

int addr_empty_timer = 1;

uint8_t HORA_APERTURA = 20;             // Hora de inicio de la operacion de vaciado (24h)
uint8_t MINUTO_APERTURA = 0;            // Minuto de inicio de la operacion de vaciado
uint8_t SEGUNDO_APERTURA = 0;           // segundo de inicio de la operacion de vaciado

uint8_t TIME_OPEN_CLOSE = 15;           // segundos para operaciones de apertura y cierre (40 segundos)
uint16_t TIME_TO_EMPTY = 35;         // segundos para vaciado del deposito (20*60 = 20 minutos)

uint8_t  listaHora[6] = {0,0,0,0,0,0};  // almacena la hora del sistema durante las modificaciones del RTC
uint8_t  listaVaciado[4] = {0,0,2,0};   // almacena la hora del vaciado programado durante su modificacion      

bool FLAG_timeout_running;              // control timeout para la luz del LCD
static uint32_t timer_luz_lcd;          // control timeout para la luz del LCD
DateTime date;                          // almacena fecha y hora actuales para tareas de control y modificacion



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//        SECCION DE CREACION DE OBJETOS
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

RTC_DS3231 rtc;                                 // creacciond de un objeto RTC
LiquidCrystal_I2C lcd(0x27,16,2);               // creacciond de un objeto LCD, (direccion, columnas, filas)
Temporizador_inopya relojControlParpadeo;       // crear temporizadores no bloqueantes
ClickButton mi_pulsador_1(PIN_PULSADOR, true);  // true=PULLUP, false= PULLDOWN


 
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ****************************************************************************************************** 
                                    FUNCION DE CONFIGURACION
   ****************************************************************************************************** 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void setup(void)
{
  pinMode(PIN_RELE_OPEN , OUTPUT);  
  pinMode(PIN_RELE_CLOSE, OUTPUT);
  pinMode(LED_ONBOARD, OUTPUT);

  digitalWrite(PIN_RELE_OPEN , OFF); 
  digitalWrite(PIN_RELE_CLOSE, OFF);

  SERIAL_BEGIN( SERIAL_BAUD_RATE );
  PRINTLN(F( __VERSION__ ));
  
	lcd.init();      //algunas librerias de LCD_I2C necesitan este modo de inicializacion
  //lcd.begin();   //algunas librerias de LCD_I2C necesitan este modo de inicializacion
  lcd.clear();
  lcd.backlight();
  
  //                              "0123456789ABCDEF"
  lcd.setCursor(0,0); lcd.print(F(" INOPYA SYSTEMS "));
  lcd.setCursor(0,1); lcd.print(F("   ** 2020 **"));
  delay(3000);
  
  //                              "0123456789ABCDEF"
  lcd.setCursor(0,0); lcd.print(F("  control para  "));
  lcd.setCursor(0,1); lcd.print(F("VACIAR DEPOSITO "));
  delay(2000);

  /* chequear si el RTC esta funcionando (de lo contrario el sistema no funcionara */
  if(! rtc.begin()) {                
    //                              "0123456789ABCDEF"
	  lcd.setCursor(0,0); lcd.print(F("   RTC FAIL     "));  
    lcd.setCursor(0,1); lcd.print(F("  SYSTEM STOP   "));
    while(true);
  }

  /* Programar fecha y hora manualmente, si procede */
  //rtc.adjust(DateTime(2019, 5, 25, 11, 28, 30));
  //rtc.adjust(DateTime(__DATE__,__TIME__));  
  //while (true);
    
	lcd.clear(); 
  //                              "0123456789ABCDEF"
  lcd.setCursor(0,0); lcd.print(F("Starting...     "));
  lcd.setCursor(0,1); lcd.print(F("  SYSTEM OK     "));
  delay(3000); 

  /* Cargar hora de vaciado desde la eeprom, si no es posible, se usara la hora por defecto 20:00 */
  bool FLAG_lectura_eeprom = read_empty_timer();
  if(!FLAG_lectura_eeprom){
    error_eeprom();
  }

  FLAG_timeout_running = true;
  date = rtc.now();
  timer_luz_lcd = date.unixtime() + TIMEOUT; 

  estado_actual = MQ_START;
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   ****************************************************************************************************** 
                                  BUCLE PRINCIPAL DEL PROGRAMA
   ****************************************************************************************************** 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/
  
void loop(void)
{ 
  date = rtc.now(); 

  horas = date.hour();
  minutos = date.minute();
  segundos = date.second();  
  uint8_t pulsacion = mi_pulsador_1.Read();

  if( pulsacion>0 ){
    lcd.backlight();
    FLAG_timeout_running = true;
    timer_luz_lcd = date.unixtime() + TIMEOUT; 
  }

  if( date.unixtime()>timer_luz_lcd && FLAG_timeout_running ){
    FLAG_timeout_running = false;
    lcd.noBacklight();
  } 

  /* Solo si ha pasado un segundo, revisamos tareas (asi evitamos molestos parpadeos del LCD) */
  if(segundos!=segundos_anterior){
    segundos_anterior = segundos;  
    pulsacion=PULSACION_NULA;
    switch (estado_actual) 
    {
      case MQ_START:
        PRINTLN_DEBUG(F("DEBUG > MQ_START"));  
        estado_actual = MQ_WAITING;
        lcd.clear();
        lcd.setCursor(0,1); 
        mostrar_proxima_apertura();
        segundos_anterior--; //para forzar el refresco
        break;
        
      case MQ_WAITING: 
        lcd.setCursor(0,0);
        if (segundos%10<7){ mostrar_hora(); }                   // mostar reloj 7 segundos
        else{ mostrar_fecha(); }                                // mostar fecha 3 segundos
        break;

      case MQ_PROG_MODE: 
        lcd.setCursor(0,0); lcd.print(F("CLICK TO SELECT ")); 
        lcd.setCursor(0,1); lcd.print(F(" (Timer/Clock)  "));
        seleccionar_programacion();
        estado_actual = MQ_START;  // retormanos el sistema a su estado inicial
        segundos_anterior--;       // para provocar el refresco de la maquina de estados/display
        date = rtc.now();
        timer_luz_lcd = date.unixtime() + TIMEOUT;
        FLAG_timeout_running = true;
        //pulsacion=PULSACION_NULA;
        break;
        
      case MQ_BEGIN_TASK:
        lcd.backlight();
        FLAG_timeout_running = false;
        PRINTLN_DEBUG(F("DEBUG > MQ_BEGIN_TASK"));  
        estado_actual = MQ_OPENNIG;
        momento_proximo_evento = date.unixtime() + TIME_OPEN_CLOSE; 
        PRINTLN_DEBUG(F("DEBUG > MQ_OPENNIG"));
        valvula_abrir();                                        // accionar valvula para abrirla
        break; 
        
      case MQ_OPENNIG:
        lcd.setCursor(0,0);
        mostrar_hora(); 
        //parpadeo_led();                                         // mostrar parpadeo lento mientras se mueve la valvula
        lcd.setCursor(0,1);
        if(segundos%2==0) {lcd.print(F(" OPENING...     ")); }  //mensaje parpadeando en pantalla
        else { borrar_linea(); }
        
        if( date.unixtime() > momento_proximo_evento ){
          estado_actual = MQ_EMPTYING;
          valor_cuenta_atras=TIME_TO_EMPTY;
          PRINTLN_DEBUG(F("DEBUG > MQ_EMPTYING"));
          lcd.setCursor(0,0);
          borrar_linea();
          lcd.setCursor(0,0);
          momento_proximo_evento=date.unixtime() + TIME_TO_EMPTY;
          valvula_reposo();                                     // permanecer abierta para proceso de vaciado
          digitalWrite (LED_ONBOARD, HIGH);                     // encender el led para indicar estado de vaciado activo
        }
        break;

      case MQ_EMPTYING: 
        lcd.setCursor(0,0);
        mostrar_cuenta_atras(valor_cuenta_atras);
        valor_cuenta_atras--;
        lcd.setCursor(0,1);
        if(segundos%2==0) { lcd.print(F(" EMPTYING TANK  ")); }  // mensaje parpadeando en pantalla
        else { borrar_linea(); }
        
        if( date.unixtime() > momento_proximo_evento ){
          valor_cuenta_atras = 0;
          estado_actual = MQ_CLOSING;
          PRINTLN_DEBUG(F("DEBUG > MQ_CLOSING"));
          momento_proximo_evento = date.unixtime() + TIME_OPEN_CLOSE; 
          valvula_cerrar();                                     // accionar valvula para cerrarla
        }
        break;
        
      case MQ_CLOSING:
        lcd.setCursor(0,0);
        mostrar_hora();
        //parpadeo_led();                                         // mostrar parpadeo lento mientras se mueve la valvula
        lcd.setCursor(0,1);
        if(segundos%2==0) {lcd.print(F(" CLOSING...     ")); }  // mensaje parpadeando en pantalla
        else { borrar_linea(); }
        
        if( date.unixtime() > momento_proximo_evento ){
          estado_actual = MQ_START;
          valvula_reposo();                                     // permanecer cerrada en espera de nuevo llenado
          digitalWrite (LED_ONBOARD, LOW);                      // apagar el led para indicar estado de reposo
          lcd.noBacklight();
        }
        break;             
    }
  }

  /* CONTROL DE PARPADEO DURANTE LS OPERACIONES DE APERTURA Y CIERRE DE LA VALVULA */
  // De este modo podemos controlar la frecuencia del parpadeo, pero se puede suprimir 
  // si se desea y usarlo desde la maquina de estados, en cuyo caso seria un parpadeo lento cada dos segundos. 
  if( estado_actual==MQ_OPENNIG || estado_actual==MQ_CLOSING ){
    if(relojControlParpadeo.estado()==false){
      relojControlParpadeo.begin(100);
      parpadeo_led();
    }
  }

  /* INICIO AUTOMATICO, ABRIR VALVULA A LA HORA PROGRAMADA */
	if ( horas==HORA_APERTURA && minutos==MINUTO_APERTURA && estado_actual==MQ_WAITING ) {
    segundos_anterior--;       // para provocar el refresco de la maquina de estados/display 
    estado_actual = MQ_BEGIN_TASK;
  }

  /* INICIO MANUAL, ABRIR VALVULA AL PULSAR, SOLO SI NO HAY OTRA OPERACION EN CURSO */
  else if( pulsacion==PULSACION_LARGA && estado_actual==MQ_WAITING ){
    segundos_anterior--;       // para provocar el refresco de la maquina de estados/display
    estado_actual = MQ_BEGIN_TASK; 
    PRINTLN_DEBUG(F("DEBUG > APERTURA MANUAL"));   
  }

  /* CANCELACION DE VACIADO EN CURSO Y CIERRE FORZADO */
  else if ( pulsacion==PULSACION_LARGA && estado_actual == MQ_EMPTYING ){
    segundos_anterior--;       // para provocar el refresco de la maquina de estados/display
    PRINTLN_DEBUG(F("DEBUG > CIERRE MANUAL"));  
    //en lugar de realizar el cierre, provocamos las condiciones para este reseteando el momento de proximo evento
    //de modo que el programa se comporta como si fuese el momento 'natural' para realizar el cierre de la valvula.
    momento_proximo_evento=0;
  }

  /* ENTRADA EN MODO PROGRAMACION */
  else if( pulsacion==PULSACION_DOBLE && estado_actual==MQ_WAITING ){
    segundos_anterior--;       // para provocar el refresco de la maquina de estados/display
    PRINTLN_DEBUG(F("DEBUG > MODIFICAR TIMER/CLOCK"));
    estado_actual=MQ_PROG_MODE; 
  }
}




/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
        BLOQUE DE FUNCIONES: LECTURAS DE SENSORES, COMUNICACION SERIE, INTERRUPCIONES...
   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/



void seleccionar_programacion()
{
  uint32_t timeOut = date.unixtime() + TIMEOUT;
  uint8_t contaMenu = 1;  
  
  /* Seleccion de objeto a modificar RTC/TIMER */
  while(date.unixtime() < timeOut){
    date = rtc.now();    
    uint8_t pulsacion = mi_pulsador_1.Read();
    if(pulsacion==PULSACION_CORTA){
      timeOut = date.unixtime() + TIMEOUT;
      contaMenu++;
      if(contaMenu%2==0){
        lcd.setCursor(0,0); lcd.print(F("PROG >> TIMER   "));
        lcd.setCursor(0,1); lcd.print(F(" (Empty Moment) "));
      }
      else{
        lcd.setCursor(0,0); lcd.print(F("PROG >> CLOCK   "));
        lcd.setCursor(0,1); lcd.print(F(" (Modify RTC)   "));
      }
    }
    else if(pulsacion==PULSACION_DOBLE){
      if(contaMenu%2==0){ modificarVaciado(); timeOut = 0; }
      else{ modificarHora(); timeOut = 0; }
    }
  }
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//  PARPADEO LED
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void parpadeo_led()
{
  digitalWrite (LED_ONBOARD, !digitalRead(LED_ONBOARD));
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    BORRAR UNA LINEA DEL LCD
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void borrar_linea()
{
  // usada en distintas aprtes para eliminar el contenido de una sola linea
  // y evitar borrados completos con lcd.clear()
  lcd.print(F("                "));
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    IMPRIMIR UN CERO EN EL LCD
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void printCero()
{
  // usada en distintas partes para formatear a dos cifras, valores numericos de una sola cifra
  lcd.print(F("0"));
}



  
/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    MOSTRAR RELOJ
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void mostrar_hora()
{  
  lcd.print(F("TIME: "));
  if(horas<10){ printCero(); }
  lcd.print(horas);
  lcd.print(F(":"));
  if(minutos<10){ printCero(); }
  lcd.print(minutos);
  lcd.print(F(":"));
  if(segundos<10){ printCero(); }
  lcd.print(segundos);
  lcd.print(F("    "));
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    MOSTRAR FECHA
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void mostrar_fecha()
{
  date = rtc.now();       
  uint8_t dias = date.day();
  uint8_t meses = date.month();
  
  lcd.print(F("DATE: "));
  if(dias<10){ printCero(); }
  lcd.print(dias);
  lcd.print(F("/"));
  if(meses<10){ printCero(); }
  lcd.print(meses);
  lcd.print(F("/"));
  lcd.print(date.year());
  lcd.print(F("    "));
}


/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    MENSAJE DE PROXIMA APERTURA DE VALVULA
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void mostrar_proxima_apertura()
{
  /* Mostar el mensaje con la hora de la proxima apertura (en modo auto)*/
  lcd.print(F("NEXT OPEN> "));
  if(HORA_APERTURA<10){ printCero(); }
  lcd.print(HORA_APERTURA);
  lcd.print(F(":"));
  if(MINUTO_APERTURA<10){ printCero(); }
  lcd.print(MINUTO_APERTURA);
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    CONTROL DE LA VALVULA
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

//========================================================
//  MOVIMIENTO DE APERTURA
//========================================================

void valvula_abrir()
{ 
  digitalWrite (PIN_RELE_OPEN , ON);
  digitalWrite (PIN_RELE_CLOSE, OFF);
}


//========================================================
//  MOVIMIENTO DE CIERRE
//========================================================

void valvula_cerrar()
{ 
  digitalWrite (PIN_RELE_OPEN , OFF);
  digitalWrite (PIN_RELE_CLOSE, ON);
}



//========================================================
//  MANTENER  EL ESTADO
//========================================================

void valvula_reposo()
{ 
  digitalWrite (PIN_RELE_OPEN , OFF);
  digitalWrite (PIN_RELE_CLOSE, OFF);
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//    MOSTAR CUENTA ATRAS DURANTE OPERACION DE VACIADO
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

void mostrar_cuenta_atras(int contador)
{
  /* Cuenta atras mostrada durante el tiempo que dura el vaciado del depósito */
  uint8_t horas;
  uint8_t minutos;
  uint8_t segundos;
  
  if (contador>=0){
    horas = contador/3600; 
    minutos = (contador-(horas*3600))/60; 
    segundos = contador-(horas*3600)-(minutos*60);

    if(horas>0){
      lcd.setCursor(3,0);
      lcd.print(F(" "));
      if(horas<10){ printCero(); }
      lcd.print(horas);
      lcd.print(F(":"));
    }
    else{
      lcd.setCursor(3,0);
      lcd.print(F("  "));
    }
    if(minutos<10){ printCero(); }
    lcd.print(minutos);
    lcd.print(F(":"));

    if(segundos<10){ printCero(); }
    lcd.print(segundos);
    lcd.print(F("   "));
  }
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//     PROGRAMAR VACIADO, HORA, FECHA 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

//========================================================
// PROGRAMAR HORA DE VACIADO
//========================================================

void modificarVaciado()
{
  uint8_t  listaPOS[4] = { CUR_VAC_HORA1, CUR_VAC_HORA2, CUR_VAC_MINU1, CUR_VAC_MINU2 };
  uint32_t tiempoEntrada = millis();

  /* separar las horas, minutos y segundos en cifras de 1 digito */
  listaVaciado[0] = HORA_APERTURA /10; 
  listaVaciado[1] = HORA_APERTURA %10;
  listaVaciado[2] = MINUTO_APERTURA /10;
  listaVaciado[3] = MINUTO_APERTURA %10;
 
  /* Reset del display */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("HORA DE VACIADO"));

  refrescar_prog_vaciado();

  bool FLAG_aceptar_cambios = false;
  uint8_t modifyIndex = 0;  
  bool FLAG_modo_PROGRAMACION = true;             // variable que nos mantiene en el bucle de modificacion de hora
  uint8_t cursorPOSh = listaPOS[modifyIndex];     // posicion del cursor de escritura para los digitos introducidos
  uint8_t CIFRA = listaVaciado[modifyIndex];         // primer valor a modificar...

  /* bucle para atencion del teclado y representacion de cifras en pantalla */
  while (FLAG_modo_PROGRAMACION == true){
    uint8_t tipoPulsacion = mi_pulsador_1.Read();   //Acceso al pulsador
    if( tipoPulsacion!=0){ delay (50);}
    if (tipoPulsacion==1){
      tiempoEntrada = millis();
      CIFRA++;
      /* comprobacion de validez de la cifra introducida */
      switch (modifyIndex){
        case 0:
          if(CIFRA==2){
            if(listaVaciado[1]>3){ listaVaciado[1]=0; }
          }
          if(CIFRA>2){CIFRA=0; }
          break;
        case 1:
          if(listaVaciado[0]==2){
            if(CIFRA>3){ CIFRA=0; }
          }
          else{
            if(CIFRA>9){ CIFRA=0; }
          }
          break;
        case 2:
          if(CIFRA>5){ CIFRA=0; }
          break;          
        case 3:
          if(CIFRA>9){ CIFRA=0; }
          break;     
      }
      listaVaciado[modifyIndex]=CIFRA;
      /* Refrescar pantalla con los nuevos valores */
      refrescar_prog_vaciado();
    }
    
    /* Gestionar el cambio de cifra a editar */
    if (tipoPulsacion==2){  //pulsacion doble cambia de cifra a editar
      modifyIndex++;
      /* mover cursor y comprobar que esta en los limites permitidos */
      if (modifyIndex >3){ modifyIndex = 0; } 
      PRINT_DEBUG(F("modifyIndex: ")); PRINTLN_DEBUG(modifyIndex);
      CIFRA=listaVaciado[modifyIndex];
      cursorPOSh=listaPOS[modifyIndex];
      refrescar_prog_vaciado();
    } 
    /* parte 1 del parpadeo del digito objetivo de posibles cambios */
    if(millis()%1200 < 600){ 
      lcd.setCursor(cursorPOSh, 1);
      lcd.print(F("_"));                 //borrar digito
    }
    /* parte 2 del parpadeo del digito objetivo de posibles cambios */
    else{
      lcd.setCursor(cursorPOSh, 1);
      lcd.print(listaVaciado[modifyIndex]);
    }


    /* control para salida si se excede un tiempo maximo inactivo */
    if (millis() > tiempoEntrada+15000){
      FLAG_modo_PROGRAMACION = false;   //No se termino la edicion, dejamos las cosas como estaban
    }

    /* salimos aceptando la edicion */
    if (tipoPulsacion==3){   //pulsacion larga
      FLAG_modo_PROGRAMACION = false;
      FLAG_aceptar_cambios = true;
    }
  }
  
  /* Aplicar los nuevos datos introducidos */
  if (FLAG_aceptar_cambios){
    HORA_APERTURA = listaVaciado[0]*10 + listaVaciado[1];
    MINUTO_APERTURA = listaVaciado[2]*10 + listaVaciado[3]; 
    bool FLAG_escritura_eeprom =  write_empty_timer(HORA_APERTURA, MINUTO_APERTURA);
    if(!FLAG_escritura_eeprom){
      error_eeprom();
    }    
  }
}


//========================================================
// MOSTRAR HORA DE VACIADO MIENTRAS SE ESTA MODIFICANDO
//========================================================

void refrescar_prog_vaciado()
{
  lcd.setCursor(CUR_VAC_HORA1, 1);
  lcd.print(listaVaciado[0]);
  lcd.print(listaVaciado[1]);
  lcd.print(F(":"));
  lcd.print(listaVaciado[2]);
  lcd.print(listaVaciado[3]);
}


//========================================================
// PROGRAMAR HORA DEL SISTEMA 
//========================================================

void modificarHora()
{
  uint8_t  listaPOS[6] = {CUR_HORA1, CUR_HORA2, CUR_MINU1, CUR_MINU2, CUR_SEGU1, CUR_SEGU2};
  uint32_t tiempoEntrada = millis();

  date = rtc.now();  

  /* separar las horas, minutos y segundos en cifras de 1 digito */
  listaHora[0] = date.hour() /10; 
  listaHora[1] = date.hour() %10;
  listaHora[2] = date.minute() /10;
  listaHora[3] = date.minute() %10;
  listaHora[4] = date.second() /10;
  listaHora[5] = date.second() %10;
  for(uint8_t x=0;x<6;x++){
    Serial.print(listaHora[x]);
  }
  Serial.println();

    
  /* Reset del display */
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTABLECER HORA"));

  refrescar_prog_hora();

  bool FLAG_aceptar_cambios = false;
  uint8_t modifyIndex = 0;  
  bool FLAG_modo_PROGRAMACION = true;             // variable que nos mantiene en el bucle de modificacion de hora
  uint8_t cursorPOSh = listaPOS[modifyIndex];     // posicion del cursor de escritura para los digitos introducidos
  uint8_t CIFRA = listaHora[modifyIndex];         // primer valor a modificar...

  /* bucle para atencion del teclado y representacion de cifras en pantalla */
  while (FLAG_modo_PROGRAMACION == true){
    uint8_t tipoPulsacion = mi_pulsador_1.Read();   //Acceso al pulsador
    if (tipoPulsacion==1){
      tiempoEntrada = millis();
      CIFRA++;
      /* comprobacion de validez de la cifra introducida */
      switch (modifyIndex){
        case 0:
          if(CIFRA==2){
            if(listaHora[1]>3){ listaHora[1]=0; }
          }
          if(CIFRA>2){CIFRA=0; }
          break;
        case 1:
          if(listaHora[0]==2){
            if(CIFRA>3){ CIFRA=0; }
          }
          else{
            if(CIFRA>9){ CIFRA=0; }
          }
          break;
        case 2:
          if(CIFRA>5){ CIFRA=0; }
          break;          
        case 3:
          if(CIFRA>9){ CIFRA=0; }
          break;
        case 4:
          if(CIFRA>5){ CIFRA=0; }
          break;      
        case 5:
          if(CIFRA>9){ CIFRA=0; }
          break;      
      }
      listaHora[modifyIndex]=CIFRA;
      refrescar_prog_hora();
    }
 
    /* Gestionar el cambio de cifra a editar */
    if (tipoPulsacion==2){  //pulsacion doble cambia de cifra a editar
      modifyIndex++;
      /* mover cursor y comprobar que esta en los limites permitidos */
      if (modifyIndex >5){ modifyIndex = 0; } 
      PRINT_DEBUG("modifyIndex: "); PRINTLN_DEBUG(modifyIndex);
      CIFRA=listaHora[modifyIndex];
      cursorPOSh=listaPOS[modifyIndex];
      refrescar_prog_hora();
    } 
    /* parte 1 del parpadeo del digito objetivo de posibles cambios */
    if(millis()%1200 < 600){ 
      lcd.setCursor(cursorPOSh, 1);
      lcd.print(F("_")); //borrar digito
    }
    /* parte 2 del parpadeo del digito objetivo de posibles cambios */
    else{
      lcd.setCursor(cursorPOSh, 1);
      lcd.print(listaHora[modifyIndex]);
    }


    /* control para salida si se excede un tiempo maximo inactivo */
    if (millis() > tiempoEntrada+25000){
      //si no se termino la edicion, dejamos las cosas como estaban
      FLAG_modo_PROGRAMACION = false;
    }

    /* salimos aceptando la edicion */
    if (tipoPulsacion==3){   //pulsacion larga, aceptar datos y terminar edicion
      FLAG_modo_PROGRAMACION = false;
      FLAG_aceptar_cambios = true;
    }
  }

  /* actualizar con los nuevos datos introducidos */
  if(FLAG_aceptar_cambios){
    byte hora =    listaHora[0]*10 + listaHora[1];
    byte minuto =  listaHora[2]*10 + listaHora[3];
    byte segundo = listaHora[4]*10 + listaHora[5];  
    date = rtc.now();            //actualizar valores de fecha/hora desde el RTC
    //rtc.adjust(DateTime(año, mes, dia, hora, minuto, segundo));
    rtc.adjust(DateTime(date.year(), date.month(), date.day(), hora, minuto, segundo));
  }
}


//========================================================
// MOSTRAR HORA DEL SISTEMA MIENTRAS SE ESTA MODIFICANDO
//========================================================

void refrescar_prog_hora()
{
  lcd.setCursor(CUR_HORA1, 1);
  lcd.print(listaHora[0]);
  lcd.print(listaHora[1]);
  lcd.print(F(":"));
  lcd.print(listaHora[2]);
  lcd.print(listaHora[3]);
  lcd.print(F(":"));
  lcd.print(listaHora[4]);
  lcd.print(listaHora[5]);
}



/*mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
//     MANEJAR DATOS EN EEPROM 
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm*/

//========================================================
// LEER HORA DE VACIADO DESDE LA EEPROM
//========================================================

bool read_empty_timer()
{
  uint8_t timer_hour = EEPROM.read(addr_empty_timer);
  uint8_t timer_minute = EEPROM.read(addr_empty_timer+1);
  /* chequear que los datos leidos son correctos */
  if(timer_hour>23 || timer_minute>59){
    return false;
  }
  HORA_APERTURA = timer_hour;             // Hora de vaciado leida de EEPROM
  MINUTO_APERTURA = timer_minute;         // Minuto de vaciado leida de EEPROM
  return true;
}


//========================================================
// GRABAR EN LA EEPROM NUEVA HORA DE VACIADO 
//========================================================

bool write_empty_timer(byte timer_hour, byte timer_minute)
{
  EEPROM.write(addr_empty_timer, timer_hour);
  EEPROM.write(addr_empty_timer+1, timer_minute);
  /* chequear que los datos se han guardado correctamente */
  if(EEPROM.read(addr_empty_timer)==timer_hour && EEPROM.read(addr_empty_timer+1)==timer_minute){
    return true;
  }
  return false;
}

//========================================================
// MENSAJE SI ERROR GRABANDO DATOS EN LA EEPROM
//========================================================
void error_eeprom()
{
  lcd.clear(); 
  lcd.setCursor(0,0); lcd.print(F("  EEPROM ERROR  "));
  lcd.setCursor(0,1); lcd.print(F("  Timer  20:00  "));
  PRINTLN_DEBUG(F("ERROR leyendo EEPROM, usadas hora de vaciado por defecto"));
  delay(3000);
}



//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************
