using MauiExcepciones.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class InMemortAuthService : IAuthService
{
    public string? CurrentUser { get; private set; }

    public bool IsLoggedIn => !string.IsNullOrEmpty(CurrentUser);

    public void Login(string username) 
    { 
    if(string.IsNullOrEmpty(username)) return;

        CurrentUser = username;
    }

    public void Logout() { 
        CurrentUser = null;
    }
}

namespace MauiExcepciones.Services
{
    internal class InMemoryAuthService
    {
    }


}
