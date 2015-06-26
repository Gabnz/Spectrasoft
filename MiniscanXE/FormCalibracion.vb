Public Class FormCalibracion
    Dim miniscan As AxMiniScanXE.AxMSXE
    Dim blancoListo As Boolean = False
    Dim negroListo As Boolean = False
    Private Sub FormCalibracion_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        btnListo.Enabled = False
    End Sub

    Sub setMiniscan(ByRef axMSXE As AxMiniScanXE.AxMSXE)
        miniscan = axMSXE
    End Sub

    Private Sub btnBlanco_Click(sender As Object, e As EventArgs) Handles btnBlanco.Click
        Try
            miniscan.ReadWhite()
            blancoListo = True
            MessageBox.Show("El color blanco se ha calibrado correctamente.", "Calibracion correcta", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("El color blanco no se ha calibrado correctamente.", "Error al calibrar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try

        If (blancoListo = True And negroListo = True) Then
            btnListo.Enabled = True
        End If
    End Sub

    Private Sub btnNegro_Click(sender As Object, e As EventArgs) Handles btnNegro.Click
        Try
            miniscan.ReadBlack()
            negroListo = True
            MessageBox.Show("El color negro se ha calibrado correctamente.", "Calibracion correcta", MessageBoxButtons.OK, MessageBoxIcon.Information)
        Catch ex As Exception
            MessageBox.Show("El color negro no se ha calibrado correctamente.", "Error al calibrar", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
        End Try

        If (blancoListo = True And negroListo = True) Then
            btnListo.Enabled = True
        End If
    End Sub

    Private Sub btnCancelar_Click(sender As Object, e As EventArgs) Handles btnCancelar.Click
        Me.Close()
    End Sub

    Private Sub btnListo_Click(sender As Object, e As EventArgs) Handles btnListo.Click
        Me.Close()
    End Sub
End Class