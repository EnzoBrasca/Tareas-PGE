using MauiExcepciones.Services;

namespace MauiExcepciones.Pages;

public partial class ExceptionsPage : ContentPage
{
    public ExceptionsPage() => InitializeComponent();

    async void OnArgNullClicked(object sender, EventArgs e)
    {
        try
        {
            string? nombre = null;

            // Prevención (guard):
            if (nombre is null)
                throw new ArgumentNullException(nameof(nombre), "El nombre es requerido.");

            _ = nombre.Length; // si pasó el guard, no falla
        }
        catch (Exception ex)
        {
            LogService.WriteLine($"[ArgNull] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }

    async void OnAoorClicked(object sender, EventArgs e)
    {
        try
        {
            int edad = -3;

            if (edad < 0 || edad > 120)
                throw new ArgumentOutOfRangeException(nameof(edad), "La edad debe estar entre 0 y 120.");

            _ = edad; // OK si es válido
        }
        catch (Exception ex)
        {
            LogService.WriteLine($"[Aoor] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }

    async void OnInvOpClicked(object sender, EventArgs e)
    {
        try
        {
            var cola = new Queue<int>();
            // Prevención: si Count == 0, no se puede Dequeue
            if (cola.Count == 0)
                throw new InvalidOperationException("No se puede extraer de una cola vacía.");

            _ = cola.Dequeue();
        }
        catch (Exception ex)
        {
            LogService.WriteLine($"[InvalidOp] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }

    async void OnFormatClicked(object sender, EventArgs e)
    {
        try
        {
            var texto = "12,34"; // según cultura, puede fallar
            if (!double.TryParse(texto, out var _))
                throw new FormatException("Formato numérico inválido para la cultura actual.");
        }
        catch (Exception ex)
        {
            LogService.WriteLine($"[Format] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }
}
