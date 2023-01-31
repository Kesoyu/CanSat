using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;
using CsvHelper;
using CsvHelper.Configuration;
using System.IO;
using System.Diagnostics;


namespace charts
{

    internal class CanSatData
    {
        struct Data
        {
            public float temp;
            public float pressure;
            public int ax;
            public int ay;
            public int az;
            public int gx;
            public int gy;
            public int gz;
            public int pm1s;
            public int pm2s;
            public int pm10s;
            public int pm1a;
            public int pm2a;
            public int pm10a;
            public bool halla;
            public Data(string t, string p, string x, string y, string z, string xx, string yy, string zz, string s1, string s2, string s10, string a1, string a2, string a10,string h)
            {
                float.TryParse(t.Replace('.', ','), out temp);
                float.TryParse(p.Replace('.', ','), out pressure);
                int.TryParse(x, out ax);
                int.TryParse(y, out ay);
                int.TryParse(z, out az);
                int.TryParse(xx, out gx);
                int.TryParse(yy, out gy);
                int.TryParse(zz, out gz);
                int.TryParse(s1, out pm1s);
                int.TryParse(s2, out pm2s);
                int.TryParse(s10, out pm10s);
                int.TryParse(a1, out pm1a);
                int.TryParse(a2, out pm2a);
                int.TryParse(a10, out pm10a);
                bool.TryParse(h, out halla);
            }
        }
        List<Data> data = new List<Data>();
        public CanSatData()
        {
            
        }
        public void ReadCSVData()
        {
            var csvConfig = new CsvConfiguration(CultureInfo.CurrentCulture)
            {
                HasHeaderRecord = false,
                Comment = '#',
                AllowComments = false,
                Delimiter = ";",
            };

            var streamReader = File.OpenText("C:\\CanSat\\CanSat\\data.csv");
            var csvReader = new CsvReader(streamReader, csvConfig);


            while (csvReader.Read())
            {
                data.Add(new Data(csvReader.GetField(0), csvReader.GetField(1), csvReader.GetField(2), csvReader.GetField(3), csvReader.GetField(4),
                                  csvReader.GetField(5), csvReader.GetField(6), csvReader.GetField(7), csvReader.GetField(8), csvReader.GetField(9),
                                  csvReader.GetField(10),csvReader.GetField(11),csvReader.GetField(12),csvReader.GetField(13),csvReader.GetField(14)));
            }
        }
    }
}
