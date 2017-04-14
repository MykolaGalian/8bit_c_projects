#define SHIFT_DATA 2
#define SHIFT_CLK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_EN 13


/*-----------------------------------------------------------------------------------------------------------------------*/
void setAddress(int address, bool outputEnable){     // установка 13 бит адреса и условия чтения-записи (главный бит из 16)
  
    shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address>>8) | (outputEnable ? 0x00 : 0x80)); // >>8 означает передачу только первых 3ёх бит числа начиная с главного бита
                                                             // если условие true то мы передаем 0 на главнй бит (OE eeprom) - для чтения
                                                            // если условие false то мы передаем 1 на главнй бит (OE eeprom) - для записи (0x80 = 0b10000000)
                                                          
    shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);    // передача младших 8 бит начиная с низшего бита
    
    digitalWrite(SHIFT_LATCH, LOW);
    digitalWrite(SHIFT_LATCH, HIGH);
    digitalWrite(SHIFT_LATCH, LOW);
  }
/*-----------------------------------------------------------------------------------------------------------------------*/
byte readEEPROM(int address){                              // чтение из памяти EEPROM

for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {             // задаем порты pin 5..12 как входы
    pinMode(pin, INPUT);
  }
 
  setAddress(address,/*outputEnable-read*/true);         // чтение - true
    byte data = 0;                                        // data - переменная в которую будем записывать данные с каждого адресуемого байта памяти EEPROM 
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {  // перебор выходов EEPROM 0...7 (входа Arduino pin 5..12)
    data = (data << 1) + digitalRead(pin);                // сдвиг в право байта данных на 1 бит в лево и на освободившееся   
  }                                                      // место запись бита данных с текущего выхода EEPROM 
   return data;
}
/*-----------------------------------------------------------------------------------------------------------------------*/

void writeEEPROM(int address, byte data) {
  setAddress(address, /*outputEnable*/ false);                        // чтение - false
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {             // задаем порты pin 5..12 как выходы
    pinMode(pin, OUTPUT);
  }

  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {             // счетчик перебора выходных портов на которые будем подавать байт информации побитно начиная с входа DO (pin 5) 
    digitalWrite(pin, data & 1);                                      // с помощью побитового "И" с маской 0b00000001 (1) задаем для заданого байта информации - последний бит неизменным, а биты перед ним будут обнулены
    data = data >> 1;                                                 // смещаем заданый байт на 1 бит вправо, для организации побитной передачи данных 
  }
  digitalWrite(WRITE_EN, LOW);                                        // после побитной установки заданого байта в порты 5..12 разрешаем заись в EEPROM путем подачи LOW 
  delayMicroseconds(1);                                               //в течении 1000ns на pin 13 и делаем паузу 10000ns перед чтением EEPROM
  digitalWrite(WRITE_EN, HIGH);
  delay(20);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
void printContents() {
  for (int base = 0; base <= 8191; base += 16) {       // создание (перебор) адресов сегментов (base) с шагом по 16 байт (в памяти от 0 до 8192 байт (8кбайт) 28с64)
                                                      
    byte tata[16];                                     // создаем переменную "tata" в которой будет хранитя массив из 16 байт прочитаных из EEPROM
    for (int offset = 0; offset <= 15; offset += 1) {  // создаем счетчик смещения (побайтно) внутри сегментов по 16 байт
      tata[offset] = readEEPROM(base + offset);        // передаем в переменную "tata" 1 байт из памяти EEPROM по текущему адресу (сегмент+смещение) в пределах текущего сегмента
      }
        char buf[80];                                  // массив - его размер должен быть не менее количества символов в строке
        sprintf(buf, "%03x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
                      base, tata[0], tata[1], tata[2], tata[3], tata[4], tata[5], tata[6], tata[7],
                            tata[8], tata[9], tata[10], tata[11], tata[12], tata[13], tata[14], tata[15]); // вывод данных на монитор порта
    Serial.println(buf);
   }
 }
/*-----------------------------------------------------------------------------------------------------------------------*/
// 4-bit hex decoder for common anode 7-segment display
//byte data[] = { 0x81, 0xcf, 0x92, 0x86, 0xcc, 0xa4, 0xa0, 0x8f, 0x80, 0x84, 0x88, 0xe0, 0xb1, 0xc2, 0xb0, 0xb8 };

// 4-bit hex decoder for common cathode 7-segment display
 byte data[] = { 0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47 };


void setup() {
  // put your setup code here, to run once:
  pinMode(SHIFT_DATA, OUTPUT);
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  digitalWrite(WRITE_EN, HIGH);  // чтобы предотваратить запись в чип когда мы этого не хотим
  pinMode(WRITE_EN, OUTPUT);      // и только после этого устанавливаем его как выход
  
  Serial.begin(57600);

 //   for (int address = 0; address <= 8191; address += 1) {   // очистка памяти
  //  writeEEPROM(address, 0xff);
  //  } 
   //  for (int address = 0; address <= 15; address += 1) {    // запись 
   // writeEEPROM(address, data[address]);
   // }

  printContents();
}



void loop() {
  // put your main code here, to run repeatedly:

}
