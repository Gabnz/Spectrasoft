<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class formPrincipal
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(formPrincipal))
        Me.btnBeep = New System.Windows.Forms.Button()
        Me.miniscan = New AxMiniScanXE.AxMSXE()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.DispositivoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ConectarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.DesconectarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SalirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PageSetupDialog1 = New System.Windows.Forms.PageSetupDialog()
        Me.btnBlanco = New System.Windows.Forms.Button()
        Me.btnNegro = New System.Windows.Forms.Button()
        Me.btnMedir = New System.Windows.Forms.Button()
        CType(Me.miniscan, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'btnBeep
        '
        Me.btnBeep.Location = New System.Drawing.Point(55, 42)
        Me.btnBeep.Name = "btnBeep"
        Me.btnBeep.Size = New System.Drawing.Size(111, 56)
        Me.btnBeep.TabIndex = 0
        Me.btnBeep.Text = "Beep"
        Me.btnBeep.UseVisualStyleBackColor = True
        '
        'miniscan
        '
        Me.miniscan.Enabled = True
        Me.miniscan.Location = New System.Drawing.Point(172, 42)
        Me.miniscan.Name = "miniscan"
        Me.miniscan.OcxState = CType(resources.GetObject("miniscan.OcxState"), System.Windows.Forms.AxHost.State)
        Me.miniscan.Size = New System.Drawing.Size(24, 26)
        Me.miniscan.TabIndex = 1
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.DispositivoToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(225, 24)
        Me.MenuStrip1.TabIndex = 2
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'DispositivoToolStripMenuItem
        '
        Me.DispositivoToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ConectarToolStripMenuItem, Me.DesconectarToolStripMenuItem, Me.SalirToolStripMenuItem})
        Me.DispositivoToolStripMenuItem.Name = "DispositivoToolStripMenuItem"
        Me.DispositivoToolStripMenuItem.Size = New System.Drawing.Size(77, 20)
        Me.DispositivoToolStripMenuItem.Text = "Dispositivo"
        '
        'ConectarToolStripMenuItem
        '
        Me.ConectarToolStripMenuItem.Name = "ConectarToolStripMenuItem"
        Me.ConectarToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ConectarToolStripMenuItem.Text = "Conectar"
        '
        'DesconectarToolStripMenuItem
        '
        Me.DesconectarToolStripMenuItem.Name = "DesconectarToolStripMenuItem"
        Me.DesconectarToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.DesconectarToolStripMenuItem.Text = "Desconectar"
        '
        'SalirToolStripMenuItem
        '
        Me.SalirToolStripMenuItem.Name = "SalirToolStripMenuItem"
        Me.SalirToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.SalirToolStripMenuItem.Text = "Salir"
        '
        'btnBlanco
        '
        Me.btnBlanco.Location = New System.Drawing.Point(55, 104)
        Me.btnBlanco.Name = "btnBlanco"
        Me.btnBlanco.Size = New System.Drawing.Size(111, 56)
        Me.btnBlanco.TabIndex = 4
        Me.btnBlanco.Text = "Calibrar blanco"
        Me.btnBlanco.UseVisualStyleBackColor = True
        '
        'btnNegro
        '
        Me.btnNegro.Location = New System.Drawing.Point(55, 166)
        Me.btnNegro.Name = "btnNegro"
        Me.btnNegro.Size = New System.Drawing.Size(111, 56)
        Me.btnNegro.TabIndex = 5
        Me.btnNegro.Text = "Calibrar negro"
        Me.btnNegro.UseVisualStyleBackColor = True
        '
        'btnMedir
        '
        Me.btnMedir.Location = New System.Drawing.Point(55, 228)
        Me.btnMedir.Name = "btnMedir"
        Me.btnMedir.Size = New System.Drawing.Size(111, 56)
        Me.btnMedir.TabIndex = 6
        Me.btnMedir.Text = "Medir"
        Me.btnMedir.UseVisualStyleBackColor = True
        '
        'formPrincipal
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(225, 307)
        Me.Controls.Add(Me.btnMedir)
        Me.Controls.Add(Me.btnNegro)
        Me.Controls.Add(Me.btnBlanco)
        Me.Controls.Add(Me.btnBeep)
        Me.Controls.Add(Me.miniscan)
        Me.Controls.Add(Me.MenuStrip1)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "formPrincipal"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "MiniscanXE"
        CType(Me.miniscan, System.ComponentModel.ISupportInitialize).EndInit()
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents btnBeep As System.Windows.Forms.Button
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents DispositivoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ConectarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DesconectarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SalirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PageSetupDialog1 As System.Windows.Forms.PageSetupDialog
    Public WithEvents miniscan As AxMiniScanXE.AxMSXE
    Friend WithEvents btnBlanco As System.Windows.Forms.Button
    Friend WithEvents btnNegro As System.Windows.Forms.Button
    Friend WithEvents btnMedir As System.Windows.Forms.Button

End Class
