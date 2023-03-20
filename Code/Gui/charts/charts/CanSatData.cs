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
            public int Index;
            public double Temp;
            public double Pressure;
            public double Temperature;
            public double Ax;
            public double Ay;
            public double Az;
            public double Yaw;
            public double Roll;
            public double Pitch;
            public double Pm1s;
            public double Pm2s;
            public double Pm10s;
            public double Pm1a;
            public double Pm2a;
            public double Pm10a;
            public double Halla;
            public int Hour;
            public int Minute;
            public int Seconds;
            public int Year;
            public int Month;
            public int Day;
            public double Latitude;
            public double Longitude;
            public char Lat;
            public char Lon;
            public double Altitude;
            public bool Antenna;
            public int Count;
            public double Blue;
            public double Yellow;
            public double Green;
            public double Other;
            public Data(string index, string temp, string pressure, string temperature,
                        string ax, string ay, string az, string yaw, string roll, string pitch,
                        string s1, string s2, string s10, string a1, string a2, string a10, string h,
                        string hour, string minute, string seconds, string year, string month, string day,
                        string latitude, string longitude, string lat, string lon, string altitude, string antenna,
                        string count, string blue, string yellow, string green, string other)
            {
                if (!int.TryParse(index, out Index))
                {
                    Temp = 0;
                }
                if (!double.TryParse(temp.Replace('.', ','), out Temp))
                {
                    Temp = 0;
                }
                if (!double.TryParse(pressure.Replace('.', ','), out Pressure))
                {
                    Pressure = 0;
                }
                if (!double.TryParse(temperature.Replace('.', ','), out Temperature))
                {
                    Pressure = 0;
                }
                if (!double.TryParse(ax.Replace('.', ','), out Ax))
                {
                    Ax = 0;
                }
                if (!double.TryParse(ay.Replace('.', ','), out Ay))
                {
                    Ay = 0;
                }
                if (!double.TryParse(az.Replace('.', ','), out Az))
                {
                    Az = 0;
                }
                if (!double.TryParse(yaw.Replace('.', ','), out Yaw))
                {
                    Yaw = 0;
                }
                if (!double.TryParse(roll.Replace('.', ','), out Roll))
                {
                    Roll = 0;
                }
                if (!double.TryParse(pitch.Replace('.', ','), out Pitch))
                {
                    Pitch = 0;
                }
                if (!double.TryParse(s1, out Pm1s))
                {
                    Pm1s = 0;
                }
                if (!double.TryParse(s2, out Pm2s))
                {
                    Pm2s = 0;
                }
                if (!double.TryParse(s10, out Pm10s))
                {
                    Pm10s = 0;
                }
                if (!double.TryParse(a1, out Pm1a))
                {
                    Pm1a = 0;
                }
                if (!double.TryParse(a2, out Pm2a))
                {
                    Pm2a = 0;
                }
                if (!double.TryParse(a10, out Pm10a))
                {
                    Pm10a = 0;
                }
                if (!double.TryParse(h, out Halla))
                {
                    Halla = 0;
                }
                if (!int.TryParse(hour, out Hour))
                {
                    Hour = 0;
                }
                if (!int.TryParse(minute, out Minute))
                {
                    Minute = 0;
                }
                if (!int.TryParse(seconds, out Seconds))
                {
                    Seconds = 0;
                }
                if (!int.TryParse(year, out Year))
                {
                    Year = 0;
                }
                if (!int.TryParse(month, out Month))
                {
                    Month = 0;
                }
                if (!int.TryParse(day, out Day))
                {
                    Day = 0;
                }
                if (!double.TryParse(latitude.Replace('.', ','), out Latitude))
                {
                    Latitude = 0;
                }
                if (!double.TryParse(longitude.Replace('.', ','), out Longitude))
                {
                    Longitude = 0;
                }
                if (!char.TryParse(lat, out Lat))
                {
                    Lat = 'X';
                }
                if (!char.TryParse(lon, out Lon))
                {
                    Lon = 'X';
                }
                if (!double.TryParse(altitude, out Altitude))
                {
                    Altitude = 0;
                }
                if (!bool.TryParse(antenna, out Antenna))
                {
                    Antenna = false;
                }
                if (!int.TryParse(count, out Count))
                {
                    Count = 0;
                }
                if (!double.TryParse(blue.Replace('.', ','), out Blue))
                {
                    Blue = 0;
                }
                if (!double.TryParse(yellow.Replace('.', ','), out Yellow))
                {
                    Yellow = 0;
                }
                if (!double.TryParse(green.Replace('.', ','), out Green))
                {
                    Green = 0;
                }
                if (!double.TryParse(other.Replace('.', ','), out Other))
                {
                    Other = 0;
                }
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

            var streamReader = File.OpenText("C:\\CanSat\\DATA.txt");
            var csvReader = new CsvReader(streamReader, csvConfig);


            while (csvReader.Read())
            {
                data.Add(new Data(csvReader.GetField(0), csvReader.GetField(1), csvReader.GetField(2), csvReader.GetField(3), csvReader.GetField(4),
                                  csvReader.GetField(5), csvReader.GetField(6), csvReader.GetField(7), csvReader.GetField(8), csvReader.GetField(9),
                                  csvReader.GetField(10), csvReader.GetField(11), csvReader.GetField(12), csvReader.GetField(13), csvReader.GetField(14),
                                  csvReader.GetField(15), csvReader.GetField(16), csvReader.GetField(17), csvReader.GetField(18), csvReader.GetField(19),
                                  csvReader.GetField(20), csvReader.GetField(21), csvReader.GetField(22), csvReader.GetField(23), csvReader.GetField(24),
                                  csvReader.GetField(25), csvReader.GetField(26), csvReader.GetField(27), csvReader.GetField(28), csvReader.GetField(29),
                                  csvReader.GetField(30), csvReader.GetField(31), csvReader.GetField(32), csvReader.GetField(33)));
            }
        }
        public void GetLastRecords(ChartValues<MeasureModel> t, ChartValues<MeasureModel> firstt, ChartValues<MeasureModel> p,
                                   ChartValues<MeasureModel> firstp, ChartValues<MeasureModel> x,
                                   ChartValues<MeasureModel> y, ChartValues<MeasureModel> z, ChartValues<MeasureModel> yaw,
                                   ChartValues<MeasureModel> roll, ChartValues<MeasureModel> pitch,
                                   ChartValues<MeasureModel> s1, ChartValues<MeasureModel> firsts1,
                                   ChartValues<MeasureModel> s2, ChartValues<MeasureModel> firsts2,
                                   ChartValues<MeasureModel> s10, ChartValues<MeasureModel> firsts10,
                                   ChartValues<MeasureModel> a1, ChartValues<MeasureModel> firsta1,
                                   ChartValues<MeasureModel> a2, ChartValues<MeasureModel> firsta2,
                                   ChartValues<MeasureModel> a10, ChartValues<MeasureModel> firsta10, ChartValues<MeasureModel> h,
                                   double cc, out string time, out string date, out string lat, out string lon,
                                   out string count, out string blue, out string yellow, out string green, out string other,
                                   out double latitude, out double longitude)
        {
            ReadCSVData();
            int helper;
            int.TryParse("" + cc, out helper);
            t.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Temp
                //Value = data.Last().temp
            });
            firstt.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Temp
                //Value = data.Last().temp
            });
            firstt.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Temp
                //Value = data.Last().temp
            });
            p.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pressure
                //Value = data.Last().pressure
            });
            firstp.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pressure
                //Value = data.Last().temp
            });
            x.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Ax
                //Value = data.Last().ax
            });
            y.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Ay
                //Value = data.Last().ay
            });
            z.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Az
                //Value = data.Last().az
            });
            yaw.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Yaw
                //Value = data.Last().gx
            });
            roll.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Roll
                //Value = data.Last().gy
            });
            pitch.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pitch
                //Value = data.Last().gz
            });
            s1.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm1s
                //Value = data.Last().pm1s
            });
            firsts1.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm1s
                //Value = data.Last().temp
            });
            s2.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm2s
                //Value = data.Last().pm2s
            });
            firsts2.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm2s
                //Value = data.Last().temp
            });
            s10.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm10s
                //Value = data.Last().pm10s
            });
            firsts10.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm10s
                //Value = data.Last().temp
            });
            a1.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm1a
                //Value = data.Last().pm1a
            });
            firsta1.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm1a
                //Value = data.Last().temp
            });
            a2.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm2a
                //Value = data.Last().pm2a

            });
            firsta2.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm2a
                //Value = data.Last().temp
            });
            a10.Add(new MeasureModel
            {
                Count = cc,
                Value = data[data.Count - 1 - helper].Pm10a
                //Value = data.Last().pm10a
            });
            firsta10.Add(new MeasureModel
            {
                Count = cc,
                Value = data.FirstOrDefault().Pm10a
                //Value = data.Last().temp
            });
            h.Add(new MeasureModel
            {
                Count = cc,
                //Value = 0
                Value = data[data.Count - 1 - helper].Halla
                //Value = data.Last().halla
            });
            time = data[data.Count - 1 - helper].Hour.ToString() + ":" + data[data.Count - 1 - helper].Minute.ToString() + ":" + data[data.Count - 1 - helper].Seconds;
            date = data[data.Count - 1 - helper].Day.ToString() + "." + data[data.Count - 1 - helper].Month.ToString() + "." + data[data.Count - 1 - helper].Year;
            lat = data[data.Count - 1 - helper].Latitude.ToString() + data[data.Count - 1 - helper].Lat.ToString();
            lon = data[data.Count - 1 - helper].Longitude.ToString() + data[data.Count - 1 - helper].Lon.ToString();
            count = data[data.Count - 1 - helper].Count.ToString();
            blue = data[data.Count - 1 - helper].Blue.ToString();
            yellow = data[data.Count - 1 - helper].Yellow.ToString();
            green = data[data.Count - 1 - helper].Green.ToString();
            other = data[data.Count - 1 - helper].Other.ToString();
            latitude = data[data.Count - 1 - helper].Latitude;
            longitude = data[data.Count - 1 - helper].Longitude;
        }
    }
}