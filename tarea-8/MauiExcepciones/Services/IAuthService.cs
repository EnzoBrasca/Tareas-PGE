using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MauiExcepciones.Services
{
    public interface IAuthService
    {
        string? CurrentUser { get; }
        bool IsLoggedIn { get; }
        void Login(string username);
        void Logout();
    }
}
