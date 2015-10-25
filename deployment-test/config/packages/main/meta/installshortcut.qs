 function Component() {
 }
 
 Component.prototype.createOperations = function() {
  component.createOperations();
 
 if ( installer.value("os") === "win" ) {
  component.addOperation(
  "CreateShortcut",
  "@TargetDir@/Spectrasoft.exe",
  "@StartMenuDir@/Spectrasoft.lnk"
  );
  
  component.addOperation(
  "CreateShortcut",
  "@TargetDir@/Desinstalar.exe",
  "@StartMenuDir@/Desinstalar.lnk"
  );
  }
 }