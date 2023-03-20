using LiveCharts;
using LiveCharts.Configurations;
using Microsoft.Maps.MapControl.WPF;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace charts
{
    /// <summary>
    /// Logika interakcji dla klasy MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        CanSatData canSatData = new CanSatData();
        Random random = new Random();
        const int length = 10;

        private double _trend;
        private double counter = 1;
        public MainWindow()
        {
            InitializeComponent();
            var mapper = Mappers.Xy<MeasureModel>()
               .X(model => model.Count)             //use DateTime.Ticks as X
               .Y(model => model.Value);            //use the value property as Y

            //lets save the mapper globally.

            Charting.For<MeasureModel>(mapper);

            hPa.LabelFormatter = val => val + " hPa";
            Celcius.LabelFormatter = val => val + " °C";
            ugm3a.LabelFormatter = val => val + " µg/m3";
            ugm3s.LabelFormatter = val => val + " µg/m3";
            degree.LabelFormatter = val => val + "°";
            ms.LabelFormatter = val => val + "m/s";
            ChartValues = new ChartValues<MeasureModel>();
            TemperatureValues = new ChartValues<MeasureModel>();
            TemperatureGroundValues = new ChartValues<MeasureModel>();
            PressureValues = new ChartValues<MeasureModel>();
            PressureGroundValues = new ChartValues<MeasureModel>();
            YawValues = new ChartValues<MeasureModel>();
            RollValues = new ChartValues<MeasureModel>();
            PitchValues = new ChartValues<MeasureModel>();
            AccXValues = new ChartValues<MeasureModel>();
            AccYValues = new ChartValues<MeasureModel>();
            AccZValues = new ChartValues<MeasureModel>();
            Pm1sValues = new ChartValues<MeasureModel>();
            Pm1sGroundValues = new ChartValues<MeasureModel>();
            Pm2sValues = new ChartValues<MeasureModel>();
            Pm2sGroundValues = new ChartValues<MeasureModel>();
            Pm10sValues = new ChartValues<MeasureModel>();
            Pm10sGroundValues = new ChartValues<MeasureModel>();
            Pm1aValues = new ChartValues<MeasureModel>();
            Pm1aGroundValues = new ChartValues<MeasureModel>();
            Pm2aValues = new ChartValues<MeasureModel>();
            Pm2aGroundValues = new ChartValues<MeasureModel>();
            Pm10aValues = new ChartValues<MeasureModel>();
            Pm10aGroundValues = new ChartValues<MeasureModel>();
            HallaValues = new ChartValues<MeasureModel>();
            Wartosc = "TEST";

            IsReading = false;

            DataContext = this;
        }
        public ChartValues<MeasureModel> ChartValues { get; set; }
        public ChartValues<MeasureModel> TemperatureValues { get; set; }
        public ChartValues<MeasureModel> TemperatureGroundValues { get; set; }
        public ChartValues<MeasureModel> PressureValues { get; set; }
        public ChartValues<MeasureModel> PressureGroundValues { get; set; }
        public ChartValues<MeasureModel> AccXValues { get; set; }
        public ChartValues<MeasureModel> AccYValues { get; set; }
        public ChartValues<MeasureModel> AccZValues { get; set; }
        public ChartValues<MeasureModel> YawValues { get; set; }
        public ChartValues<MeasureModel> RollValues { get; set; }
        public ChartValues<MeasureModel> PitchValues { get; set; }
        public ChartValues<MeasureModel> Pm1sValues { get; set; }
        public ChartValues<MeasureModel> Pm1sGroundValues { get; set; }
        public ChartValues<MeasureModel> Pm2sValues { get; set; }
        public ChartValues<MeasureModel> Pm2sGroundValues { get; set; }
        public ChartValues<MeasureModel> Pm10sValues { get; set; }
        public ChartValues<MeasureModel> Pm10sGroundValues { get; set; }
        public ChartValues<MeasureModel> Pm1aValues { get; set; }
        public ChartValues<MeasureModel> Pm1aGroundValues { get; set; }
        public ChartValues<MeasureModel> Pm2aValues { get; set; }
        public ChartValues<MeasureModel> Pm2aGroundValues { get; set; }
        public ChartValues<MeasureModel> Pm10aValues { get; set; }
        public ChartValues<MeasureModel> Pm10aGroundValues { get; set; }
        public ChartValues<MeasureModel> HallaValues { get; set; }

        private string _value;
        public string Wartosc
        {
            get
            {
                return _value;
            }
            set
            {
                _value = value;
                OnPropertyChanged("Wartosc");
            }
        }

        public bool IsReading { get; set; }

        private void Read()
        {
            var r = new Random();

            while (IsReading)
            {
                string Time = string.Empty;
                string Date = string.Empty;
                string Lat = string.Empty;
                string Lon = string.Empty;
                string Count = string.Empty;
                string Blue = string.Empty;
                string Yellow = string.Empty;
                string Green = string.Empty;
                string Other = string.Empty;
                double Latitude = 0;
                double Longitude = 0;

                Thread.Sleep(1000);
                var now = DateTime.Now;

                _trend = r.Next(-20, 20);

                ChartValues.Add(new MeasureModel
                {
                    Count = counter,
                    Value = _trend
                });
                canSatData.GetLastRecords(TemperatureValues, TemperatureGroundValues,
                                          PressureValues, PressureGroundValues,
                                          AccXValues, AccYValues, AccZValues,
                                          YawValues, RollValues, PitchValues,
                                          Pm1sValues, Pm1sGroundValues,
                                          Pm2sValues, Pm2sGroundValues,
                                          Pm10sValues, Pm10sGroundValues,
                                          Pm1aValues, Pm1aGroundValues,
                                          Pm2aValues, Pm2aGroundValues,
                                          Pm10aValues, Pm10aGroundValues, HallaValues,
                                          counter, out Time, out Date, out Lat, out Lon,
                                          out Count, out Blue, out Yellow, out Green, out Other, out Latitude, out Longitude);
                counter++;
                SetGPS(Time, Date, Lat, Lon);
                SetPixy(Count, Blue, Yellow, Green, Other);
                SetMap(Latitude, Longitude);

                //lets only use the last 50 values
                if (ChartValues.Count >= 50)
                {
                    ChartValues.Clear();
                    TemperatureValues.Clear();
                    TemperatureGroundValues.Clear();
                    PressureValues.Clear();
                    PressureGroundValues.Clear();
                    AccXValues.Clear();
                    AccYValues.Clear();
                    AccZValues.Clear();
                    YawValues.Clear();
                    RollValues.Clear();
                    PitchValues.Clear();
                    Pm1sValues.Clear();
                    Pm1sGroundValues.Clear();
                    Pm2sValues.Clear();
                    Pm2sGroundValues.Clear();
                    Pm10sValues.Clear();
                    Pm10sGroundValues.Clear();
                    Pm1aValues.Clear();
                    Pm1aGroundValues.Clear();
                    Pm2aValues.Clear();
                    Pm2aGroundValues.Clear();
                    Pm10aValues.Clear();
                    Pm10aGroundValues.Clear();
                    HallaValues.Clear();
                    counter = 1;
                }
            }
        }
        private void SetMap(double latitude, double longitude)
        {
            latitude = latitude / 100;
            longitude = longitude / 100;
            Dispatcher.Invoke(new Action(() => {
                MapMap.Center = new Location(latitude, longitude);
            }));
        }
        private void SetPixy(string count, string blue, string yellow, string green, string other)
        {
            Dispatcher.Invoke(new Action(() => {
                Count.Text = "Count: " + count;
                Blue.Text = "Blue: " + blue + "%";
                Yellow.Text = "Yellow: " + yellow + "%";
                Green.Text = "Green: " + green + "%";
                Other.Text = "Other: " + other + "%";
            }));
        }
        private void SetGPS(string time, string date, string lat, string lon)
        {
            Dispatcher.Invoke(new Action(() => {
                Time.Text = "Time: " + time;
                Date.Text = "Date: " + date;
                Latitude.Text = "Latitude: " + lat;
                Longitude.Text = "Longitude: " + lon;
            }));
        }

        private void InjectStopOnClick(object sender, RoutedEventArgs e)
        {
            IsReading = !IsReading;
            if (IsReading) Task.Factory.StartNew(Read);
        }

        #region INotifyPropertyChanged implementation

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName = null)
        {
            if (PropertyChanged != null)
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion

        public ChartValues<double> generateRandomArray()
        {
            ChartValues<double> arr = new ChartValues<double>();
            for (int i = 0; i < length; i++)
            {
                double value = new double();
                int rdm = random.Next(1, 10);
                double.TryParse("" + rdm, out value);
                arr.Add(value);
            }
            return arr;
        }
    }
}