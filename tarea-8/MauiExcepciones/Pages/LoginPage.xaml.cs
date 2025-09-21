using MauiExcepciones.Services;

namespace MauiExcepciones.Pages;

public partial class LoginPage : ContentPage
{
    private readonly IAuthService _authService;
    private readonly FakeAuthService _service;
    public LoginPage(InMemortAuthService service)
    {
        InitializeComponent();
        _authService = service;
    }

    protected override void OnAppearing()
    {
        base.OnAppearing();
        UserEntry.Text = _authService.CurrentUser;
    }

    async void OnLoginClicked(object sender, EventArgs e)
    {
        try
        {
            Busy.IsVisible = Busy.IsRunning = true;
            LoginBtn.IsEnabled = false;

            // VALIDACIÓN de dominio (guard clauses)
            var user = UserEntry.Text?.Trim() ?? string.Empty;
            var pass = PassEntry.Text?.Trim() ?? string.Empty;

            if (string.IsNullOrWhiteSpace(user))
                throw new ArgumentNullException(nameof(user), "Usuario vacío.");
            if (string.IsNullOrWhiteSpace(pass))
                throw new ArgumentNullException(nameof(pass), "Clave vacía.");
            if (user.Length < 3 || user.Length > 20)
                throw new ArgumentOutOfRangeException(nameof(user), "Usuario fuera de longitud (3–20).");
            if (pass.Length < 3 || pass.Length > 20)
                throw new ArgumentOutOfRangeException(nameof(pass), "Clave fuera de longitud (3–20).");

            // “Llamada” remota con timeout de 2.5s
            var ok = await _service.LoginAsync(user, pass, TimeSpan.FromSeconds(2.5));

            ResultLabel.Text = ok ? "Resultado: acceso concedido ✅" : "Resultado: credenciales inválidas ❌";
        }
        catch (Exception ex) when (ex is HttpRequestException || ex is TaskCanceledException || ex is ArgumentNullException || ex is ArgumentOutOfRangeException)
        {
            LogService.WriteLine($"[Login] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Atención", ExceptionMapper.ToUserMessage(ex), "OK");
            ResultLabel.Text = "Resultado: error de comunicación o validación";
        }
        finally
        {
            Busy.IsVisible = Busy.IsRunning = false;
            LoginBtn.IsEnabled = true;
        }
    }
}
