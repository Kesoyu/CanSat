using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace charts
{
    public class StringModel : ObservableObject
    {
        private string _value;
        public string Value{
            get{
                return _value;
            }
            set
            {
                _value = value;
                OnPropertyChanged();
            }
        }
    }
}
