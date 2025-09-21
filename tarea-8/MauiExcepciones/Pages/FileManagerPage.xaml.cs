using MauiExcepciones.Services;
using System.Text;

namespace MauiExcepciones.Pages;

public partial class FileManagerPage : ContentPage
{
    public FileManagerPage() => InitializeComponent();

    string FullPath(string file) => Path.Combine(FileSystem.AppDataDirectory, file);

    async void OnGuardarClicked(object sender, EventArgs e)
    {
        try
        {
            var file = FileNameEntry.Text?.Trim();
            if (string.IsNullOrWhiteSpace(file))
                throw new ArgumentNullException(nameof(file));

            var path = FullPath(file);

            // using/IDisposable: FileStream + StreamWriter
            using var fs = new FileStream(path, FileMode.Create, FileAccess.Write, FileShare.Read);
            using var sw = new StreamWriter(fs, Encoding.UTF8);
            await sw.WriteAsync(TextEditor.Text ?? string.Empty);

            StatusLabel.Text = $"Estado: guardado en {path}";
        }
        catch (Exception ex) when (ex is UnauthorizedAccessException || ex is IOException || ex is ArgumentNullException)
        {
            LogService.WriteLine($"[Guardar] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Error", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }

    async void OnAbrirClicked(object sender, EventArgs e)
    {
        try
        {
            var file = FileNameEntry.Text?.Trim();
            if (string.IsNullOrWhiteSpace(file))
                throw new ArgumentNullException(nameof(file));

            var path = FullPath(file);

            // Lanzará FileNotFoundException si no existe (lo capturamos)
            if (!File.Exists(path))
                throw new FileNotFoundException("No existe", path);

            using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
            using var sr = new StreamReader(fs, Encoding.UTF8);
            var content = await sr.ReadToEndAsync();

            TextEditor.Text = content;
            StatusLabel.Text = $"Estado: abierto {path}";
        }
        catch (Exception ex) when (ex is FileNotFoundException || ex is UnauthorizedAccessException || ex is IOException || ex is ArgumentNullException)
        {
            LogService.WriteLine($"[Abrir] {ex.GetType().Name} - {ex.Message}");
            await DisplayAlert("Error", ExceptionMapper.ToUserMessage(ex), "OK");
        }
    }

    async void OnDuplicarClicked(object sender, EventArgs e)
    {
        var file = FileNameEntry.Text?.Trim();
        if (string.IsNullOrWhiteSpace(file))
            throw new ArgumentNullException(nameof(file));

        var path = FullPath(file);

        var NombreArchivoNuevo = $"{Path.GetFileNameWithoutExtension(file)}";
        var pathDest =  FullPath(NombreArchivoNuevo);
        try
        {
            File.Copy(path, pathDest);

            await DisplayAlert("Exito", $"archivo duplicado como '{NombreArchivoNuevo}'", "OK");
            FileNameEntry.Text = NombreArchivoNuevo;
            UpdateFileInfoLabel(pathDest);
        }
        catch (FileNotFoundException)
        {
            await DisplayAlert("Error", $"El archivo de origen '{file}' no fue encontrado. No se puede duplicar.", "OK");
        }
        catch (UnauthorizedAccessException)
        {
            await DisplayAlert("Error de Permisos", "La aplicación no tiene los permisos necesarios para acceder o crear el archivo en esta ubicación.", "OK");
        }
        catch (IOException ex)
        {
            // IOException es común si el archivo de destino ya existe o hay problemas de disco.
            await DisplayAlert("Error de E/S", $"Ocurrió un error de entrada/salida. Es posible que el archivo '{NombreArchivoNuevo}' ya exista o que el disco esté lleno. Detalles: {ex.Message}", "OK");
        }
        catch (Exception ex)
        {
            // Un catch genérico para cualquier otro error inesperado.
            await DisplayAlert("Error Inesperado", $"Ocurrió un error al duplicar: {ex.Message}", "OK");
        }
    }
    private void UpdateFileInfoLabel(string filePath)
    {
        try
        {
            if (File.Exists(filePath))
            {
                var fileInfo = new FileInfo(filePath);
                DateTime lastModified = fileInfo.LastWriteTime;
                long sizeInBytes = fileInfo.Length;

                StatusLabel.Text = $"Última modificación: {lastModified:dd/MM/yyyy HH:mm:ss}\nTamaño: {sizeInBytes} bytes";
            }
            else
            {
                StatusLabel.Text = "El archivo no existe.";
            }
        }
        catch (Exception ex)
        {
            StatusLabel.Text = $"No se pudo obtener la información del archivo. Error: {ex.Message}";
        }
    }
}
