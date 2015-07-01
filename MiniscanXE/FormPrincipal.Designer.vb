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
        Dim ChartArea1 As System.Windows.Forms.DataVisualization.Charting.ChartArea = New System.Windows.Forms.DataVisualization.Charting.ChartArea()
        Dim Legend1 As System.Windows.Forms.DataVisualization.Charting.Legend = New System.Windows.Forms.DataVisualization.Charting.Legend()
        Dim Series1 As System.Windows.Forms.DataVisualization.Charting.Series = New System.Windows.Forms.DataVisualization.Charting.Series()
        Me.miniscan = New AxMiniScanXE.AxMSXE()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.DispositivoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ConectarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.DesconectarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SalirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpcionesToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BeepToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CalibrarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.btnMedir = New System.Windows.Forms.Button()
        Me.chartReflectancia = New System.Windows.Forms.DataVisualization.Charting.Chart()
        Me.btnArchivo = New System.Windows.Forms.Button()
        CType(Me.miniscan, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.MenuStrip1.SuspendLayout()
        CType(Me.chartReflectancia, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'miniscan
        '
        Me.miniscan.Enabled = True
        Me.miniscan.Location = New System.Drawing.Point(12, 27)
        Me.miniscan.Name = "miniscan"
        Me.miniscan.OcxState = CType(resources.GetObject("miniscan.OcxState"), System.Windows.Forms.AxHost.State)
        Me.miniscan.Size = New System.Drawing.Size(24, 26)
        Me.miniscan.TabIndex = 1
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.DispositivoToolStripMenuItem, Me.OpcionesToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(681, 24)
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
        'OpcionesToolStripMenuItem
        '
        Me.OpcionesToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.BeepToolStripMenuItem, Me.CalibrarToolStripMenuItem})
        Me.OpcionesToolStripMenuItem.Name = "OpcionesToolStripMenuItem"
        Me.OpcionesToolStripMenuItem.Size = New System.Drawing.Size(69, 20)
        Me.OpcionesToolStripMenuItem.Text = "Opciones"
        '
        'BeepToolStripMenuItem
        '
        Me.BeepToolStripMenuItem.Name = "BeepToolStripMenuItem"
        Me.BeepToolStripMenuItem.Size = New System.Drawing.Size(115, 22)
        Me.BeepToolStripMenuItem.Text = "Beep"
        '
        'CalibrarToolStripMenuItem
        '
        Me.CalibrarToolStripMenuItem.Name = "CalibrarToolStripMenuItem"
        Me.CalibrarToolStripMenuItem.Size = New System.Drawing.Size(115, 22)
        Me.CalibrarToolStripMenuItem.Text = "Calibrar"
        '
        'btnMedir
        '
        Me.btnMedir.Location = New System.Drawing.Point(259, 99)
        Me.btnMedir.Name = "btnMedir"
        Me.btnMedir.Size = New System.Drawing.Size(80, 26)
        Me.btnMedir.TabIndex = 6
        Me.btnMedir.Text = "Medir"
        Me.btnMedir.UseVisualStyleBackColor = True
        '
        'chartReflectancia
        '
        Me.chartReflectancia.BorderlineColor = System.Drawing.Color.Transparent
        ChartArea1.Name = "ChartArea1"
        Me.chartReflectancia.ChartAreas.Add(ChartArea1)
        Legend1.Name = "Legend1"
        Me.chartReflectancia.Legends.Add(Legend1)
        Me.chartReflectancia.Location = New System.Drawing.Point(73, 171)
        Me.chartReflectancia.Name = "chartReflectancia"
        Series1.ChartArea = "ChartArea1"
        Series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line
        Series1.Legend = "Legend1"
        Series1.Name = "Series1"
        Me.chartReflectancia.Series.Add(Series1)
        Me.chartReflectancia.Size = New System.Drawing.Size(545, 257)
        Me.chartReflectancia.TabIndex = 7
        Me.chartReflectancia.Text = "Curva de reflectancia"
        '
        'btnArchivo
        '
        Me.btnArchivo.Location = New System.Drawing.Point(345, 99)
        Me.btnArchivo.Name = "btnArchivo"
        Me.btnArchivo.Size = New System.Drawing.Size(80, 26)
        Me.btnArchivo.TabIndex = 8
        Me.btnArchivo.Text = "Leer archivo"
        Me.btnArchivo.UseVisualStyleBackColor = True
        '
        'formPrincipal
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(681, 477)
        Me.Controls.Add(Me.btnArchivo)
        Me.Controls.Add(Me.chartReflectancia)
        Me.Controls.Add(Me.btnMedir)
        Me.Controls.Add(Me.miniscan)
        Me.Controls.Add(Me.MenuStrip1)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "formPrincipal"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "MiniscanXE"
        CType(Me.miniscan, System.ComponentModel.ISupportInitialize).EndInit()
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        CType(Me.chartReflectancia, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents DispositivoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ConectarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DesconectarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SalirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Public WithEvents miniscan As AxMiniScanXE.AxMSXE
    Friend WithEvents btnMedir As System.Windows.Forms.Button
    Friend WithEvents OpcionesToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CalibrarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BeepToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents chartReflectancia As System.Windows.Forms.DataVisualization.Charting.Chart
    Friend WithEvents btnArchivo As System.Windows.Forms.Button

End Class
