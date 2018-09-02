
//--------------------------------------------------------------
//       Autor del Programa: Konrad Peschka
//       Fecha: Septiembre 2017
//--------------------------------------------------------------

#include <Adafruit_NeoPixel.h>

#define PIN            10
#define NUMPIXELS      8


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


#include <Servo.h>

//-------------------------------------------------------------------
//      Definicion Alias de cada servo y los Pines del Arduino
//-------------------------------------------------------------------

#define servo1_pin 8      // Pin Frente Derecha Cuerpo
#define servo2_pin 7      // Pin Atras Derecha Cuerpo
#define servo3_pin 3      // Pin Atras Izquierda Cuerpo
#define servo4_pin 4      // Pin Frente Izquierda Cuerpo

#define servo5_pin 9     // Pin Frente Derecha Pata
#define servo6_pin 6     // Pin Atras Derecha Pata
#define servo7_pin 2     // Pin Atras Izquierda Pata
#define servo8_pin 5     // Pin Frente Izquierda Pata

//-------------------------------------------------------------------
//  Definicion de las constantes posicion inicial de cada servo
//-------------------------------------------------------------------

//subir = giro antihor en cuerpo y patas

#define servo1_centro     1400      //Frente_derecha_cuerpo_centro
#define servo2_centro     1400      //Atras_derecha_cuerpo_centro
#define servo3_centro     1400      //Atras_Izquierda_cuerpo_centro
#define servo4_centro     1400      //Frente_Izquierda_cuerpo_centro

#define servo5_centro      2200      //Frente_derecha_pata_centro
#define servo6_centro      2200      //Atras_derecha_pata_centro
#define servo7_centro      2200      //Atras_Izquierda_pata_centro
#define servo8_centro      2200      //Frente_Izquierda_pata_centro

//-------------------------------------------------------------------

int levanta_pata = 300;
int levanta_pata2 = 800;

int pata_hacia_frente = 800;

int movimiento_izq;
int movimiento_der;

int contador_sentarse;
int distancia_actual = 0;

int aux = 0;  //auxiliar que utilizo para las funciones especiales
int variable_sienta = 1500;

int tiempo_entre_servo = 70;

const int tiempo_sienta = 50;
int brillo = 50;

int auxiliar_saluda = 0;
int auxiliar_sienta = 0;

//-------------------------------------------------------------------
//       Defino como le va a llamar cada servo
//-------------------------------------------------------------------

Servo servo1;        // Frente Derecha Cuerpo
Servo servo2;       // Atras Derecha Cuerpo
Servo servo3;        // Atras Izquierda Cuerpo
Servo servo4;         // Frente Izquierda Cuerpo

Servo servo5;       // Frente Derecha Pata
Servo servo6;       // Atras Derecha Pata
Servo servo7;        // Atras Izquierda Pata
Servo servo8;      // Frente Izquierda Pata


//-------------------------------------------------------------------
//                 Seteo de Entradas, salidas y funciones
//-------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pixels.begin();

  //activa luces rojas
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(brillo, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(200); // Delay for a period of time (in milliseconds).
  }

  //muestro blanco
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, brillo, brillo)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(1); // Delay for a period of time (in milliseconds).
  }

}

//-------------------------------------------------------------------
//         Sector donde comienza la funcion Principal,
//        Donde se va a quedar el resto de la ejecucion
//-------------------------------------------------------------------

char auxColor;

void loop() {
  char variable = 'X';
  if (Serial.available()) {
    variable = Serial.read();

  }

  switch (variable) {
    case 'Y':
      apagar_servos();
      delay(50);
      Serial.write(variable);
      break;
    case 'Z':
      activar_servos();
      delay(50);
      posicion_reposo();
      delay(50);
      Serial.write(variable);
      break;

    case 'F':
      Camina_frente();
      Serial.write(variable);
      break;
    case 'B':
      camina_atras();
      Serial.write(variable);
      break;
    case 'L':
      Gira_izq();
      Serial.write(variable);
      break;
    case 'R':
      Gira_der() ;
      Serial.write(variable);
      break;
    case 'S':
      auxiliar_saluda = 0;
      auxiliar_sienta = 0;
      posicion_reposo();
      Serial.write(variable);
      break;

    case 'I':
      if (auxiliar_sienta == 0)
      {
        sienta();
        auxiliar_sienta = 1;
      }
      Serial.write(variable);
      break;

    case 'O':
      if (auxiliar_saluda == 0)
      {
        sienta_para_saludar();
        auxiliar_saluda = 1;
      }
      mueve_pata_frente();
      Serial.write(variable);
      break;

    case 'E':
      patea_izquierda();
      Serial.write(variable);
      break;

    case 'A':
      patea_derecha();
      Serial.write(variable);
      break;
    case 'C':
      mostrarColor(brillo, brillo, 0);
      delay(50);
      auxColor = Serial.read();
      if (auxColor == '0')
        mostrarColor(0, 0, 0);
      else if (auxColor == '1')
        mostrarColor(brillo, 0, 0);
      else if (auxColor == '2')
        mostrarColor(brillo, 0, brillo);
      else if (auxColor == '3')
        mostrarColor(0, 0, brillo);
      else if (auxColor == '4')
        mostrarColor(0, brillo, brillo);
      else if (auxColor == '5')
        mostrarColor(0, brillo, 0);
      else if (auxColor == '6')
        mostrarColor(brillo, brillo, 0);
      else if (auxColor == '7')
        mostrarColor(brillo, brillo, brillo);
      

      Serial.write(variable);
      //activar_servos();
      break;
    case 'V':
      tiempo_entre_servo = map(Serial.parseInt(), 0, 4, 100, 30);
      Serial.write(variable);
      break;
    case 'b':
      brillo = map(Serial.parseInt(), 0, 9, 0, 50);
      mostrarColor(brillo, brillo, brillo);
      Serial.write(variable);
      break;
  }

}

/*  --------  Activar Servos ---------   */

void activar_servos(void)
{
  servo1.attach(servo1_pin);
  servo1.writeMicroseconds(servo1_centro);

  servo2.attach(servo2_pin);
  servo2.writeMicroseconds(servo2_centro);

  servo3.attach(servo3_pin);
  servo3.writeMicroseconds(servo3_centro);

  servo4.attach(servo4_pin);
  servo4.writeMicroseconds(servo4_centro);

  servo5.attach(servo5_pin);
  servo5.writeMicroseconds(servo5_centro );

  servo6.attach(servo6_pin);
  servo6.writeMicroseconds(servo6_centro );

  servo7.attach(servo7_pin);
  servo7.writeMicroseconds(servo7_centro );

  servo8.attach(servo8_pin);
  servo8.writeMicroseconds(servo8_centro );

  delay(tiempo_entre_servo);
}

/*  --------  Desactivar Servos ---------   */

void apagar_servos(void)
{
  servo1.detach();
  servo2.detach();
  servo3.detach();
  servo4.detach();
  servo5.detach();
  servo6.detach();
  servo7.detach();
  servo8.detach();
  delay(tiempo_entre_servo);
}
//------------------------Funcion donde todos los servos van a reposo---------------

void posicion_reposo(void)
{
  servo1.writeMicroseconds(servo1_centro);
  delay(tiempo_entre_servo);
  servo2.writeMicroseconds(servo2_centro);
  delay(tiempo_entre_servo);
  servo3.writeMicroseconds(servo3_centro);
  delay(tiempo_entre_servo);
  servo4.writeMicroseconds(servo4_centro);
  delay(tiempo_entre_servo);
  servo5.writeMicroseconds(servo5_centro );
  delay(tiempo_entre_servo);
  servo6.writeMicroseconds(servo6_centro );
  delay(tiempo_entre_servo);
  servo7.writeMicroseconds(servo7_centro );
  delay(tiempo_entre_servo);
  servo8.writeMicroseconds(servo8_centro );
  delay(tiempo_entre_servo);

}

//--------------------Movimiento Base--------------------

void movimiento_base(void)
{
  // ----------------sube las patas 8 y 6 ------------------
  servo6.writeMicroseconds(servo6_centro - levanta_pata);
  delay(tiempo_entre_servo);
  servo8.writeMicroseconds(servo8_centro - levanta_pata);
  delay(tiempo_entre_servo);

  // -------------avanza todas las patas-------------------
  servo4.writeMicroseconds(servo4_centro + movimiento_izq);
  servo2.writeMicroseconds(servo2_centro - movimiento_der);
  servo1.writeMicroseconds(servo1_centro + movimiento_der);
  servo3.writeMicroseconds(servo3_centro - movimiento_izq);
  delay(tiempo_entre_servo);

  // ----------------baja las patas 8 y 6 ------------------
  servo6.writeMicroseconds(servo6_centro );
  delay(tiempo_entre_servo);
  servo8.writeMicroseconds(servo8_centro );
  delay(tiempo_entre_servo);

  //----------levanta las patas 5 y 7-----------------
  servo7.writeMicroseconds(servo7_centro - levanta_pata);
  delay(tiempo_entre_servo);
  servo5.writeMicroseconds(servo5_centro - levanta_pata);
  delay(tiempo_entre_servo);

  // -------------avanza todas las patas-------------------
  servo1.writeMicroseconds(servo1_centro - movimiento_der);
  servo3.writeMicroseconds(servo3_centro + movimiento_izq);
  servo4.writeMicroseconds(servo4_centro - movimiento_izq);
  servo2.writeMicroseconds(servo2_centro + movimiento_der);
  delay(tiempo_entre_servo);

  // ----------------baja las patas 5 y 7 ------------------
  servo7.writeMicroseconds(servo7_centro );
  delay(tiempo_entre_servo);
  servo5.writeMicroseconds(servo5_centro );
  delay(tiempo_entre_servo);

}

// -----------------------------------Funcion Avanzar hacia el frente-----------------------

void Camina_frente()
{
  movimiento_izq = 300;
  movimiento_der = 300;
  movimiento_base();
}

// -----------------------------------Funcion Gira Derecha------------------------------------
void Gira_der()
{
  movimiento_izq = -300;
  movimiento_der = 300;
  movimiento_base();
}

// -----------------------------------Funcion Gira Izquierda----------------------------------
void Gira_izq()
{
  movimiento_izq = 300;
  movimiento_der = -300;
  movimiento_base();
}

// -----------------------------------Funcion Camina hacia Atras-------------------------------
void camina_atras()
{
  movimiento_izq = -300;
  movimiento_der = -300;
  movimiento_base();
}

//--------------------funcion con al cual se sienta--------------------

void sienta(void)
{
  servo1.writeMicroseconds(servo1_centro);
  delay(tiempo_entre_servo);
  servo4.writeMicroseconds(servo4_centro);
  delay(tiempo_entre_servo);

  servo2.writeMicroseconds(servo2_centro - variable_sienta / 3); //se tira de a poco
  delay(tiempo_entre_servo);
  servo3.writeMicroseconds(servo3_centro + variable_sienta / 3);
  delay(tiempo_entre_servo);
  servo6.writeMicroseconds(servo6_centro - variable_sienta / 3);
  delay(tiempo_entre_servo);
  servo7.writeMicroseconds(servo7_centro - variable_sienta / 3);
  delay(tiempo_entre_servo);

  servo2.writeMicroseconds(servo2_centro - variable_sienta / 2); //se tira de a poco
  delay(tiempo_entre_servo);
  servo3.writeMicroseconds(servo3_centro + variable_sienta / 2);
  delay(tiempo_entre_servo);
  servo6.writeMicroseconds(servo6_centro - variable_sienta / 2);
  delay(tiempo_entre_servo);
  servo7.writeMicroseconds(servo7_centro - variable_sienta / 2);
  delay(tiempo_entre_servo);

  servo2.writeMicroseconds(servo2_centro - variable_sienta / 2); //se termina de tirar
  delay(tiempo_entre_servo);
  servo3.writeMicroseconds(servo3_centro + variable_sienta / 2);
  delay(tiempo_entre_servo);
}

//-------------------se tira para mover las patas y saludar---------------------

void sienta_para_saludar(void)
{
  servo1.writeMicroseconds(servo1_centro);
  delay(tiempo_entre_servo / 2);
  servo4.writeMicroseconds(servo4_centro);
  delay(tiempo_entre_servo / 2);

  servo2.writeMicroseconds(servo2_centro - variable_sienta / 2); //se tira al piso de costado
  delay(tiempo_entre_servo / 2);
  // servo3.writeMicroseconds(servo3_centro - variable_sienta / 2);
  // delay(tiempo_entre_servo / 2);

  servo5.writeMicroseconds(servo5_centro - variable_sienta);
  delay(tiempo_entre_servo / 2);
  servo7.writeMicroseconds(servo7_centro - variable_sienta / 3);
  delay(tiempo_entre_servo / 2);
  servo7.writeMicroseconds(servo7_centro - variable_sienta / 2);
  delay(tiempo_entre_servo / 2);
  servo7.writeMicroseconds(servo7_centro - variable_sienta);
  delay(tiempo_entre_servo / 2);
  servo7.writeMicroseconds(servo6_centro - variable_sienta);
  delay(tiempo_entre_servo / 2);
}

//--------------Funcion Mueve Pata en Frente cuando saluda---------------

void mueve_pata_frente(void)
{
  int maximo = 500;
  for (int j = 0; j < maximo; j = j + 100)
  {
    servo1.writeMicroseconds(servo1_centro + j); //se tira al piso de costado
    delay(tiempo_entre_servo);
  }

  for (int j = maximo; j > 0; j = j - 100)
  {
    servo1.writeMicroseconds(servo1_centro + j); //se tira al piso de costado
    delay(tiempo_entre_servo);
  }

  for (int j = 0; j < maximo; j = j + 100)
  {
    servo1.writeMicroseconds(servo1_centro - j); //se tira al piso de costado
    delay(tiempo_entre_servo);
  }

  for (int j = maximo; j > 0; j = j - 100)
  {
    servo1.writeMicroseconds(servo1_centro - j); //se tira al piso de costado
    delay(tiempo_entre_servo);
  }
}


//------------------Funcion donde patea del lazo izquierdo-----------------

void patea_derecha(void)
{
  servo1.writeMicroseconds(servo1_centro - pata_hacia_frente);
  delay(tiempo_entre_servo * 4);
  servo7.writeMicroseconds(servo7_centro - levanta_pata);
  delay(tiempo_entre_servo * 6);
  servo5.writeMicroseconds(servo5_centro - levanta_pata2);
  delay(tiempo_entre_servo * 6);
  servo5.writeMicroseconds(servo5_centro);
  delay(tiempo_entre_servo);
  servo1.writeMicroseconds(servo1_centro);
  delay(tiempo_entre_servo);
}
//------------------Funcion donde patea del lazo izquierdo-----------------

void patea_izquierda(void)
{
  servo4.writeMicroseconds(servo4_centro + pata_hacia_frente);
  delay(tiempo_entre_servo * 4);
  servo6.writeMicroseconds(servo6_centro - levanta_pata);
  delay(tiempo_entre_servo * 6);
  servo8.writeMicroseconds(servo8_centro - levanta_pata2);
  delay(tiempo_entre_servo * 6);
  servo8.writeMicroseconds(servo8_centro );
  delay(tiempo_entre_servo);
  servo4.writeMicroseconds(servo4_centro);
  delay(tiempo_entre_servo);
}

void mostrarColor(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(200); // Delay for a period of time (in milliseconds).
  }
}

//
//-------------------------------------------------------------------
//               FIN PROGRAMA
//-------------------------------------------------------------------


