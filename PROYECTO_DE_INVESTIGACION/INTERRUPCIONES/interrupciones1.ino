
//En la siguiente grafica se evidencia la implementación de una alarma de seguridad con una placa Arduino Uno, un sensor PIR, un buzzer y unos cuantos Leds

// pin de entrada de sensor
const int Sensor = 2; //Se utiliza en pin 2 debido a que la placa Arduino UNO solo soporta interrupciones en los puertos 2 y 3. 


// pines de salida de los leds
const int LED = 4;
const int LED_R = 5;
const int LED_B=6;

bool alarma = false; // Para implementarse en la interrupcion. 

void setup() { 
  // Aquí indicamos a la plata que función tendrá cada puerto.
  pinMode(Sensor,INPUT);
  pinMode(LED,OUTPUT);

  pinMode(LED_R,OUTPUT);
  pinMode(LED_B,OUTPUT);
  digitalWrite(LED_R,LOW);
  digitalWrite(LED_B,LOW);

  attachInterrupt(digitalPinToInterrupt(Sensor),interrumpir,RISING); // Si el estado del pin especificado cambia, se llamará a la funcion imterrumpir.

}

void interrumpir(){
  // La función interrumpir se encargar de cambiar el valor de la variable alarma a True, en caso de ser activada la irrupción por el sensor.
  alarma  = true;
}

void loop() {
  //En el loop tenemos un condicional que en caso de ser True el valor de la alarma nos activa las luces led y buzeer intermitentemente. 
  if(alarma)
  {
    for(int i = 0; i<30;i++)
    {
      digitalWrite(LED_R,HIGH);
      digitalWrite(LED_B, LOW);
      delay(100);
      digitalWrite(LED_B,HIGH);
      digitalWrite(LED_R,LOW);
      delay(100);
    }
    alarma=false;
  }
  else
  {
    //En caso de que el valor de la variable alarma sea False se activa un led de manera intermitente indicando al usuario que el dispositivo está en funcionamiento.
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_B, LOW);

    if(digitalRead(LED) == HIGH)
    {
      digitalWrite (LED,LOW);
    }
    else
    {
      digitalWrite (LED,HIGH);
    }
    delay(500);
  }
}
