<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class FormCalibracion
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.btnNegro = New System.Windows.Forms.Button()
        Me.btnBlanco = New System.Windows.Forms.Button()
        Me.btnListo = New System.Windows.Forms.Button()
        Me.btnCancelar = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'btnNegro
        '
        Me.btnNegro.Location = New System.Drawing.Point(69, 90)
        Me.btnNegro.Name = "btnNegro"
        Me.btnNegro.Size = New System.Drawing.Size(111, 56)
        Me.btnNegro.TabIndex = 7
        Me.btnNegro.Text = "Calibrar negro"
        Me.btnNegro.UseVisualStyleBackColor = True
        '
        'btnBlanco
        '
        Me.btnBlanco.Location = New System.Drawing.Point(69, 28)
        Me.btnBlanco.Name = "btnBlanco"
        Me.btnBlanco.Size = New System.Drawing.Size(111, 56)
        Me.btnBlanco.TabIndex = 6
        Me.btnBlanco.Text = "Calibrar blanco"
        Me.btnBlanco.UseVisualStyleBackColor = True
        '
        'btnListo
        '
        Me.btnListo.Location = New System.Drawing.Point(24, 165)
        Me.btnListo.Name = "btnListo"
        Me.btnListo.Size = New System.Drawing.Size(94, 31)
        Me.btnListo.TabIndex = 8
        Me.btnListo.Text = "Listo"
        Me.btnListo.UseVisualStyleBackColor = True
        '
        'btnCancelar
        '
        Me.btnCancelar.Location = New System.Drawing.Point(124, 165)
        Me.btnCancelar.Name = "btnCancelar"
        Me.btnCancelar.Size = New System.Drawing.Size(94, 31)
        Me.btnCancelar.TabIndex = 9
        Me.btnCancelar.Text = "Cancelar"
        Me.btnCancelar.UseVisualStyleBackColor = True
        '
        'FormCalibracion
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(248, 208)
        Me.Controls.Add(Me.btnCancelar)
        Me.Controls.Add(Me.btnListo)
        Me.Controls.Add(Me.btnNegro)
        Me.Controls.Add(Me.btnBlanco)
        Me.Name = "FormCalibracion"
        Me.Text = "FormCalibracion"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents btnNegro As System.Windows.Forms.Button
    Friend WithEvents btnBlanco As System.Windows.Forms.Button
    Friend WithEvents btnListo As System.Windows.Forms.Button
    Friend WithEvents btnCancelar As System.Windows.Forms.Button
End Class
