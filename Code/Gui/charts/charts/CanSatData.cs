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
using LiveCharts;
using System.Reflection;
using System.Runtime.InteropServices;


namespace charts
{

    internal class CanSatData
    {
        struct Data
        {
            public double temp;
            public double pressure;
            public double ax;
            public double ay;
            public double az;
            public double gx;
            public double gy;
            public double gz;
            public double pm1s;
            public double pm2s;
            public double pm10s;
            public double pm1a;
            public double pm2a;
            public double pm10a;
            public double halla;
            public Data(string t, string p, string x, string y, string z, string xx, string yy, string zz, string s1, string s2, string s10, string a1, string a2, string a10,string h)
            {
                double.TryParse(t.Replace('.', ','), out temp);
                double.TryParse(p.Replace('.', ','), out pressure);
                double.TryParse(x, out ax);
                double.TryParse(y, out ay);
                double.TryParse(z, out az);
                double.TryParse(xx, out gx);
                double.TryParse(yy, out gy);
                double.TryParse(zz, out gz);
                double.TryParse(s1, out pm1s);
                double.TryParse(s2, out pm2s);
                double.TryParse(s10, out pm10s);
                double.TryParse(a1, out pm1a);
                double.TryParse(a2, out pm2a);
                double.TryParse(a10, out pm10a);
                double.TryParse(h, out halla);
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
        public void GetLastRecords(ChartValues<MeasureModel> t, ChartValues<MeasureModel> p, ChartValues<MeasureModel> x,
                                   ChartValues<MeasureModel> y, ChartValues<MeasureModel> z, ChartValues<MeasureModel> xx,
                                   ChartValues<MeasureModel> yy, ChartValues<MeasureModel> zz, ChartValues<MeasureModel> s1,
                                   ChartValues<MeasureModel> s2, ChartValues<MeasureModel> s10, ChartValues<MeasureModel> a1,
                                   ChartValues<MeasureModel> a2, ChartValues<MeasureModel> a10, ChartValues<MeasureModel> h,
                                   double cc)
        {
            ReadCSVData();
            int helper;
            int.TryParse(""+cc, out helper);
            t.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count-1-helper].temp
            });
            p.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pressure
            });
            x.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].ax
            });
            y.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].ay
            });
            z.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].az
            });
            xx.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].gx
            });
            yy.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].gy
            });
            zz.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].gz
            });
            s1.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm1s
            });
            s2.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm2s
            });
            s2.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm10s
            });
            a1.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm1a            
            });
            a2.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm2a
            });
            a10.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].pm10a
            });
            h.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].halla
            });
        }
    }
}
