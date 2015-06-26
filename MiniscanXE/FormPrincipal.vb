Public Class formPrincipal

    Dim conectado As Boolean
    Dim blancoListo As Boolean
    Dim negroListo As Boolean
    Const PUNTOS_ESPECTRALES As Integer = 31

    Private Sub btnBeep_Click(sender As Object, e As EventArgs) Handles btnBeep.Click

        Try
            miniscan.Beep()
        Catch ex As Exception

        End Try

    End Sub

    Private Sub formPrincipal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.btnBeep.Enabled = False
        Me.btnBlanco.Enabled = False
        Me.btnNegro.Enabled = False
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
            Me.btnBeep.Enabled = True
            Me.btnBlanco.Enabled = True
            Me.btnNegro.Enabled = True
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
        Me.btnBeep.Enabled = False
        Me.btnBlanco.Enabled = False
        Me.btnNegro.Enabled = False
        Me.btnMedir.Enabled = False
    End Sub

    Private Sub btnBlanco_Click(sender As Object, e As EventArgs) Handles btnBlanco.Click
        Try
            miniscan.ReadWhite()
            blancoListo = True
            MessageBox.Show("El color blanco se ha calibrado correctamente.", "Calibracion correcta", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("El color blanco no se ha calibrado correctamente.", "Error al calibrar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try


    End Sub

    Private Sub btnNegro_Click(sender As Object, e As EventArgs) Handles btnNegro.Click
        Try
            miniscan.ReadBlack()
            negroListo = True
            MessageBox.Show("El color negro se ha calibrado correctamente.", "Calibracion correcta", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("El color negro no se ha calibrado correctamente.", "Error al calibrar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try
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
End Class
