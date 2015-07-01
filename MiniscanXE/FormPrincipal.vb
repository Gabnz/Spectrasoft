Imports System.IO

Public Class formPrincipal

    Dim conectado As Boolean
    Dim curvaGenerada As Boolean = False
    Const PUNTOS_ESPECTRALES As Integer = 31

    Private Sub btnBeep_Click(sender As Object, e As EventArgs)

        Try
            miniscan.Beep()
        Catch ex As Exception

        End Try

    End Sub

    Private Sub formPrincipal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.BeepToolStripMenuItem.Enabled = False
        Me.CalibrarToolStripMenuItem.Enabled = False
        Me.btnMedir.Enabled = False
        Me.DesconectarToolStripMenuItem.Enabled = False
        conectado = False
        Me.MinimumSize = Me.Size
        Me.MaximumSize = Me.Size
        Me.MaximizeBox = False
    End Sub

    Private Sub ConectarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ConectarToolStripMenuItem.Click
        miniscan.CommPort = 3
        miniscan.BaudRate = 9600

        Try
            miniscan.OpenCommPort()
            conectado = True
            MessageBox.Show("El dispositivo se ha conectado correctamente.", "Conectado", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("Verifique que el dispositivo este conectado correctamente.", "Error al conectar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try

        If (conectado) Then
            Me.ConectarToolStripMenuItem.Enabled = False
            Me.DesconectarToolStripMenuItem.Enabled = True
            Me.BeepToolStripMenuItem.Enabled = True
            Me.CalibrarToolStripMenuItem.Enabled = True
            Me.btnMedir.Enabled = True
        End If

    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Try
            miniscan.CloseCommPort()
        Catch ex As Exception

        End Try

        Me.Close()
    End Sub

    Private Sub DesconectarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DesconectarToolStripMenuItem.Click

        Try
            miniscan.CloseCommPort()
            MessageBox.Show("El dispositivo se ha desconectado correctamente.", "Desconectado", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("El dispositivo no se logro desconectar correctamente.", "Error al desconectar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try

        Me.ConectarToolStripMenuItem.Enabled = True
        Me.DesconectarToolStripMenuItem.Enabled = False
        Me.BeepToolStripMenuItem.Enabled = False
        Me.CalibrarToolStripMenuItem.Enabled = False
        Me.btnMedir.Enabled = False
    End Sub

    Private Sub btnMedir_Click(sender As Object, e As EventArgs) Handles btnMedir.Click
        Dim resultado(PUNTOS_ESPECTRALES) As Single
        Dim flag As Boolean = False

        Debug.Print("Empieza nueva medicion")

        Try
            miniscan.ReadSample(resultado)
            flag = True
            MessageBox.Show("La medicion se llevo a cabo correctamente.", "Medicion correcta", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("Hubo un error al intentar realizar la medicion.", "Error al medir", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try

        If (flag) Then
            For Each valor In resultado
                Debug.WriteLine(valor)

            Next
        End If
    End Sub

    Private Sub CalibrarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CalibrarToolStripMenuItem.Click
        Dim fCalib As FormCalibracion
        fCalib = New FormCalibracion
        fCalib.setMiniscan(miniscan)
        fCalib.Show()
    End Sub

    Private Sub BeepToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles BeepToolStripMenuItem.Click
        Try
            miniscan.Beep()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub btnArchivo_Click(sender As Object, e As EventArgs) Handles btnArchivo.Click
        Dim resultado(PUNTOS_ESPECTRALES) As Single
        Dim flag As Boolean = False

        If (curvaGenerada = False) Then
            Try
                Using sr As New StreamReader("D:\Code\tesis-CIMBUC\MiniscanXE\MiniscanXE\datosPrueba.txt")
                    Dim line As String
                    Dim i As Integer = 0
                    Dim val As Single
                    line = sr.ReadLine 'lee la primera linea para desecharla, puesto que siempre es cero (0)

                    chartReflectancia.ResetAutoValues()

                    For i = 1 To PUNTOS_ESPECTRALES

                        line = sr.ReadLine
                        val = Single.Parse(line)
                        chartReflectancia.Series(0).Points.AddY(val)
                    Next
                End Using
                curvaGenerada = True
            Catch ex As Exception
                Debug.WriteLine("El archivo no se pudo leer:")
                Debug.WriteLine(ex.Message)
            End Try
        End If

    End Sub
End Class
