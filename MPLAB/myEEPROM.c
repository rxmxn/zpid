/*
EXPLICACION:
  float data;
  int8 x;
  x = *(((int8*)&data + i));
  1-Cuando se referencia 'data' (&) se accede a la direccion donde esta almacenado ese float
  2-Se castea como (int8*), accediendo a solo 8 bits de esa direccion
  3-Se realiza un desplazamiento de 8 bits en 8 bits en dependencia de la i
  4-Se castea la direccion completa como *, es decir, se apunta a esa direccion
  5-El resultado 'x' sera el valor almacenado en esa direccion de memoria 
*/

void write_float_eeprom(int8 address, float data) 
{
   int i;
   
   for(i=0;i<4;i++)
     write_eeprom(i + address, *(((int8*)&data + i)));
}

float read_float_eeprom(int8 address)        
{
   int i;
   float data;

   for(i=0;i<4;i++)
     *(((int8*)&data) + i) = read_eeprom(i + address);

   return data;
}

void write_int16_eeprom(int8 address, int16 data)
{
  write_eeprom(address,data);
  write_eeprom(address+1,data/0x100);
}

signed int16 read_int16_eeprom(int8 address)
{
  return read_eeprom(address+1)*0x100 + read_eeprom(address);
}
