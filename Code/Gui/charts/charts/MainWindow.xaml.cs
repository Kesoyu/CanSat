﻿using LiveCharts;
using LiveCharts.Configurations;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
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

        //private double _axisMax;
        //private double _axisMin;
        private double _trend;
        private double counter = 1;
        public MainWindow()
        {
            InitializeComponent();
            var mapper = Mappers.Xy<MeasureModel>()
               .X(model => model.Count)   //use DateTime.Ticks as X
               .Y(model => model.Value);           //use the value property as Y

            //lets save the mapper globally.
            Charting.For<MeasureModel>(mapper);

            hPa.LabelFormatter = val => val + " hPa";
            Celcius.LabelFormatter = val => val + " °C";
            ugm3.LabelFormatter = val => val + " µg/m3";
            //the values property will store our values array
            ChartValues = new ChartValues<MeasureModel>();
            TemperatureValues = new ChartValues<MeasureModel>();
            PressureValues = new ChartValues<MeasureModel>();
            GeoXValues = new ChartValues<MeasureModel>();
            GeoYValues = new ChartValues<MeasureModel>();
            GeoZValues = new ChartValues<MeasureModel>();
            AccXValues = new ChartValues<MeasureModel>();
            AccYValues = new ChartValues<MeasureModel>();
            AccZValues = new ChartValues<MeasureModel>();
            Pm1sValues = new ChartValues<MeasureModel>();
            Pm2sValues = new ChartValues<MeasureModel>();
            Pm10sValues = new ChartValues<MeasureModel>();
            Pm1aValues = new ChartValues<MeasureModel>();
            Pm2aValues = new ChartValues<MeasureModel>();
            Pm10aValues = new ChartValues<MeasureModel>();
            HallaValues = new ChartValues<MeasureModel>();

            //lets set how to display the X Labels
            //DateTimeFormatter = value => new DateTime((long)value).ToString("mm:ss");

            //AxisStep forces the distance between each separator in the X axis
            //AxisStep = TimeSpan.FromSeconds(1).Ticks;
            //AxisUnit forces lets the axis know that we are plotting seconds
            //this is not always necessary, but it can prevent wrong labeling
            //AxisUnit = TimeSpan.TicksPerSecond;

            //SetAxisLimits(DateTime.Now);

            //The next code simulates data changes every 300 ms

            IsReading = false;

            DataContext = this;
        }
        public ChartValues<MeasureModel> ChartValues { get; set; }
        public ChartValues<MeasureModel> TemperatureValues { get; set; }
        public ChartValues<MeasureModel> PressureValues { get; set; }
        public ChartValues<MeasureModel> GeoXValues { get; set; }
        public ChartValues<MeasureModel> GeoYValues { get; set; }
        public ChartValues<MeasureModel> GeoZValues { get; set; }
        public ChartValues<MeasureModel> AccXValues { get; set; }
        public ChartValues<MeasureModel> AccYValues { get; set; }
        public ChartValues<MeasureModel> AccZValues { get; set; }
        public ChartValues<MeasureModel> Pm1sValues { get; set; }
        public ChartValues<MeasureModel> Pm2sValues { get; set; }
        public ChartValues<MeasureModel> Pm10sValues { get; set; }
        public ChartValues<MeasureModel> Pm1aValues { get; set; }
        public ChartValues<MeasureModel> Pm2aValues { get; set; }
        public ChartValues<MeasureModel> Pm10aValues { get; set; }
        public ChartValues<MeasureModel> HallaValues { get; set; }
        //public Func<double, string> DateTimeFormatter { get; set; }
/*        public double AxisStep { get; set; }
        public double AxisUnit { get; set; }

        public double AxisMax
        {
            get { return _axisMax; }
            set
            {
                _axisMax = value;
                OnPropertyChanged("AxisMax");
            }
        }
        public double AxisMin
        {
            get { return _axisMin; }
            set
            {
                _axisMin = value;
                OnPropertyChanged("AxisMin");
            }
        }*/

        public bool IsReading { get; set; }

        private void Read()
        {
            var r = new Random();

            while (IsReading)
            {
                Thread.Sleep(1000);
                var now = DateTime.Now;

                _trend = r.Next(-20, 20);

                ChartValues.Add(new MeasureModel
                {
                    Count = counter,
                    Value = _trend
                });
                canSatData.GetLastRecords(TemperatureValues, PressureValues, AccXValues, AccYValues, AccZValues,
                                          GeoXValues, GeoYValues, GeoZValues, Pm1sValues, Pm2sValues, Pm10sValues,
                                          Pm1aValues, Pm2aValues, Pm10aValues, HallaValues, counter);
                counter++;

                //SetAxisLimits(now);

                //lets only use the last 50 values
                if (ChartValues.Count >= 50)
                {
                    ChartValues.Clear();
                    TemperatureValues.Clear();
                    PressureValues.Clear();
                    AccXValues.Clear();
                    AccYValues.Clear();
                    AccZValues.Clear();
                    GeoXValues.Clear();
                    GeoYValues.Clear();
                    GeoZValues.Clear();
                    Pm1sValues.Clear();
                    Pm2sValues.Clear();
                    Pm10sValues.Clear();
                    Pm1aValues.Clear();
                    Pm2aValues.Clear();
                    Pm10aValues.Clear();
                    HallaValues.Clear();
                    counter = 1;
                }
            }
        }

       /* private void SetAxisLimits(DateTime now)
        {
            AxisMax = now.Ticks + TimeSpan.FromSeconds(1).Ticks; // lets force the axis to be 1 second ahead
            AxisMin = now.Ticks - TimeSpan.FromSeconds(8).Ticks; // and 8 seconds behind
        }*/

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
            for(int i=0;i<length;i++)
            {
                double value = new double();
                int rdm = random.Next(1,10);
                double.TryParse(""+rdm, out value);
                arr.Add(value);
            }
            return arr;
        }
    }
}
