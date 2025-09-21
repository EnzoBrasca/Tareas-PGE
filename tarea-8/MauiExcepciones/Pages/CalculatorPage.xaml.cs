
using MauiExcepciones.Services;

namespace MauiExcepciones.Pages;

public partial class CalculatorPage : ContentPage
{
    public CalculatorPage() => InitializeComponent();

    async void OnCalcularClicked(object sender, EventArgs e)
    {
        var operationDescription = "No especificada";

        try
        {
            // VALIDACI�N: si TryParse falla, lanzamos FormatException expl�cita
            if (!double.TryParse(Num1Entry.Text, out var a) ||
                !double.TryParse(Num2Entry.Text, out var b))
                throw new FormatException("Entradas no num�ricas.");

            var op = OpPicker.SelectedIndex;
            if (op < 0) throw new InvalidOperationException("Seleccion� una operaci�n.");

            operationDescription = OpPicker.SelectedItem?.ToString() ?? "Desconocida";

            double r = op switch
            {
                0 => a + b,
                1 => a - b,
                2 => a * b,
                3 => b == 0 ? throw new DivideByZeroException() : a / b,
                4 => Math.Pow(a, b),
                5 => b <= 0 ? throw new ArgumentOutOfRangeException(): Math.Pow(a, (1.00 / b)),
                _ => throw new InvalidOperationException("Operaci�n desconocida.")
            };

            ResultLabel.Text = $"Resultado: {r}";
        }
        catch (Exception ex)
        {
            // Log t�cnico + mensaje seguro
            LogService.WriteLine($"[Calc] {ex.GetType().Name} - {ex.Message} [Operacion] {operationDescription}");
            await DisplayAlert("Atenci�n", ExceptionMapper.ToUserMessage(ex), "OK");
        }
        finally
        {
            // Ejemplo de finally: reestablecer UI
            (sender as Button)!.IsEnabled = true;
        }
    }

    async void OnVerLogClicked(object sender, EventArgs e)
    {
        await DisplayAlert("Log", LogService.ReadAll(), "OK");
    }
}
