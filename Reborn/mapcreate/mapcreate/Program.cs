using System;
using System.IO;
using System.Linq;
using System.Text;

namespace mapcreate
{
    class gracz
    {

        public void getdata() {
            int[] spell_value = { 1, 2, 4, 8, 16, 32, 64, 128 };                           /// Spell values
            int[] spellbuffor = { 0 };                                                      /// Subbuffor - for counting the spell sum
            char[] buffer;                                                                /// Internal buffer for file reading (max 16 signs)

            for (int i = 0; i < 11; i++)
            {

            }
        }

        public void writedata()
        {

        }
    }

    class main
    {
        // DEFINICJA MAPY
        int[] loc = { 11774, 11912 };
        int[] offset = { 0, 9, 10, 26, 28, 56, 57, 90, 92, 93, 110, 100 };                          //	#DEFINE offsets - locations of each element in the map memory
        int[] jump = { 1, 2, 2, 4, 4, 2, 2, 1, 1, 1, 1, 1 };                                        //	#DEFINE jumps	- to overcome problem of overwriting, program is "jumping" over the map memory


        // DEFINICJA PARSERA
        int[] icount = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 4, 72 };                                  // Number of elements			(1 hero_name, 7 creatures' type, 7 creatures' amount, 72 spells)
        int[] isize = { 3, 3, 1, 5, 5, 3, 3, 3, 3, 3, 3, 1 };                                       // Amount of signs per element	(127 heroes = 3 signs, maximum 30 000 creatures -  5 signs, 1 spell bool 0/1 )
        /// Offset in input file reading


        //DEFINICJA PLIKU WYJŚCIOWEGO
        //FILE* output;
        int[] ecount = { 1, 8, 8, 7, 7, 16, 16, 2, 1, 1, 4, 9 };                      /// Number of output elements	(the difference is in spells, since the output is 9 spell sums, not 72 bools)						
        int[][] buffor;																/// output buffor 8 players * 8 heroes * 12 parameters per hero
        int[] wsize = { 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1 };


        static void Main(string[] args)
        {

            byte rodzajBohatera = 102;

            byte[] rodzajUmiejetnosci = {2,3,4,5,6 };
            byte[] poziomUmiejetnosci = {1,1,1,1,1 };


            UInt16[] rodzajJednostki = { 10, 20, 30, 40, 50, 60, 70 };
            UInt16[] iloscJednostki = { 100, 200, 300, 400, 500, 600, 700 };

            byte[] rodzajArtefaktu = { 19, 42, 33, 7, 16, 25, 37, 45, 255, 255, 255, 255, 255 };
            byte[] boolArtefaktu = { 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255 };
            
            byte miscFive = 46;
            byte boolMiscFive=  0;

            byte boolSpellBook = 0;

            byte[] iloscStatystyk = { 20, 21, 22, 23 };

            byte[] ksiegaZaklec = {0, 1, 3, 7, 15, 31, 63, 127, 255 };

            using (Stream stream = new FileStream("D:/GOG Games/HoMM 3 Complete/random_maps/mapkaa2.h3m", FileMode.OpenOrCreate))
            {

                // zapis BOHATERA
                    stream.Seek(11774, SeekOrigin.Begin);
                    byte[] array = BitConverter.GetBytes(rodzajBohatera);
                    stream.Write(array, 0, 1);

                // zapis UMIEJETNOSCI

                for (int i = 0; i < 5; i++)
                {
                    stream.Seek(11774 + 9 + 2 * i, SeekOrigin.Begin);
                    byte[] bArray = BitConverter.GetBytes(rodzajUmiejetnosci[i]);
                    stream.Write(bArray, 0, 1);

                    stream.Seek(11774 + 10 + 2 * i, SeekOrigin.Begin);
                    byte[] bArrayb = BitConverter.GetBytes(poziomUmiejetnosci[i]);
                    stream.Write(bArrayb, 0, 1);
                }

                // zapis JEDNOSTEK

                for (int i = 0; i<7; i++)
                {
                    stream.Seek(11774 + 20+4*i, SeekOrigin.Begin);  
                    byte[] bArray = BitConverter.GetBytes(rodzajJednostki[i]);
                    stream.Write(bArray, 0, bArray.Length);

                    stream.Seek(11774 + 22 + 4 * i, SeekOrigin.Begin);
                    byte[] bArrayb = BitConverter.GetBytes(iloscJednostki[i]);
                    stream.Write(bArrayb, 0, bArray.Length);
                }
                
                //zapis ARTEFAKTÓW
                for (int i=0; i<13; i++)
                { 
                    stream.Seek(11774 + 50 + 2 * i, SeekOrigin.Begin);
                    byte[] bArray = BitConverter.GetBytes(rodzajArtefaktu[i]);
                    stream.Write(bArray, 0, 1);

                    
                    stream.Seek(11774 + 51 + 2 * i, SeekOrigin.Begin);
                    byte[] bArrayb = BitConverter.GetBytes(boolArtefaktu[i]);
                    stream.Write(bArrayb, 0, 1);
                }

                // zapis Spell Booka
                    stream.Seek(11774 + 84, SeekOrigin.Begin);
                    byte[] arrayd = BitConverter.GetBytes(boolSpellBook);
                    stream.Write(arrayd, 0, 1);
                    stream.Seek(11774 + 85, SeekOrigin.Begin);
                    stream.Write(arrayd, 0, 1);

                // zapis MISC 5
                    stream.Seek(11774 + 86, SeekOrigin.Begin);
                    byte[] arrayb = BitConverter.GetBytes(miscFive);
                    stream.Write(arrayb, 0, 1);

                    stream.Seek(11774 + 87, SeekOrigin.Begin);
                    byte[] arrayc = BitConverter.GetBytes(boolMiscFive);
                    stream.Write(arrayc, 0, 1);

                // zapis Spelli
                for (int i = 0; i < 9; i++)
                {
                    stream.Seek(11774 + 94 + i, SeekOrigin.Begin);
                    byte[] bArray = BitConverter.GetBytes(ksiegaZaklec[i]);
                    stream.Write(bArray, 0, 1);
                }
            }

        }
    }
}
