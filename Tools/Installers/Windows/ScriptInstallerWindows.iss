// sinT Windows installer script for Windows (InnoSetup) -> GitHub - AlbertoNR98

#define AppName "sinT"
#define AppVersion "1.0.0"
#define AppPublisher "AlbertoNR98"
#define AppURL "https://www.github.com/AlbertoNR98/sinT"
#define AppExeName "sinT.exe"
#define ExecutableDir "" ; Path where the .exe is located before creating the installer -> e.g. "C:\Users\Alberto\Desktop\sinT\Builds\VisualStudio2022\x64\Release\Standalone Plugin\sinT.exe"
#define KioskDir "" ; Path where the .exe is located before creating the installerr -> e.g. "C:\Users\Alberto\Desktop\sinT\Builds\VisualStudio2022\x64\Release_Kiosk\Standalone Plugin\sinT.exe"
#define VST3PluginDir "" ; Path where the VST plugin is located before creating the installer  -> e.g. "C:\Users\Alberto\Desktop\sinT\Builds\VisualStudio2022\x64\Release\VST3\sinT.vst3"
#define PresetsDir "" ; Factory presets path -> e.g. "C:\Users\Alberto\Desktop\sinT\Presets\*"

[Setup]
AppId={{E0641DF8-F290-4BC4-87C1-7740FAE1490F}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#AppPublisher}
AppPublisherURL={#AppURL}
AppSupportURL={#AppURL}
AppUpdatesURL={#AppURL}
DefaultDirName={autopf}\{#AppName}
DefaultGroupName={#AppName}
OutputBaseFilename="{#AppName}_{#AppVersion}_win_installer"
AllowNoIcons=yes
Compression=lzma
SolidCompression=yes
WizardStyle=modern
; UninstallDisplayIcon={code:GetDir|0}\{#AppName}
UninstallFilesDir={code:GetDir|0}
DisableWelcomePage=no
LicenseFile=GPL_3_0_License.txt
DisableDirPage=yes
DisableProgramGroupPage=yes

[Types]
//Name: "full"; Description: "Full installation";
Name: "standaloneVST3"; Description: "Standalone version + VST3 plugin installation";
Name: "standalone"; Description: "Standalone version installation";
Name: "kiosk"; Description: "Kiosk mode installation";

[Components]
Name: "standalonecomp"; Description: "sinT Standalone Version"; Types: standalone standaloneVST3;
Name: "kioskcomp"; Description: "sinT Kiosk Mode Version"; Types: kiosk;
Name: "vst3comp"; Description: "sinT VST3 Plugin Version"; Types: standaloneVST3;

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; 

[Files]
Source: "{#ExecutableDir}"; DestDir: "{code:GetDir|0}"; Flags: ignoreversion; Components: standalonecomp
Source: "{#KioskDir}"; DestDir: "{code:GetDir|0}"; Flags: ignoreversion; Components: kioskcomp
Source: "{#VST3PluginDir}"; DestDir: "{code:GetDir|1}"; Flags: ignoreversion; Components: vst3comp
Source: "{#PresetsDir}"; DestDir: "{%HOMEPATH}\sinT\Presets"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#AppName}"; Filename: "{code:GetDir|0}\{#AppExeName}"
Name: "{group}\{cm:UninstallProgram,{#AppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#AppName}"; Filename: "{code:GetDir|0}\{#AppExeName}"; Tasks: desktopicon

[Code]
var
  DataDirPage: TInputDirWizardPage; 

procedure InitializeWizard;
begin
  // Installation directory selection view
  DataDirPage := CreateInputDirPage(wpSelectDir,
    'Select Installation Directories', 'Where do you want to install sinT components?',
    'Select the folder in which Setup should install standalone and VST3, then click Next.',
    False, 'sinT');

  DataDirPage.Add('Standalone or kiosk version installation folder');
  DataDirPage.Add('VST3 plugin version installation folder');

  DataDirPage.Values[0] := GetPreviousData('StandaloneDir', ExpandConstant('{autopf}') + '\sinT');
  DataDirPage.Values[1] := GetPreviousData('VST3Dir', 'C:\VST3');
end;

// Stores the selected directories in case you want to do a later reinstallation or update
procedure RegisterPreviousData(PreviousDataKey: Integer);
begin
  SetPreviousData(PreviousDataKey, 'StandaloneDir', DataDirPage.Values[0]);
  SetPreviousData(PreviousDataKey, 'KioskDir', DataDirPage.Values[0]);
  SetPreviousData(PreviousDataKey, 'VST3Dir', DataDirPage.Values[1]);
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  // Default directory if empty
  if DataDirPage.Values[0] = '' then
     DataDirPage.Values[0] := ExpandConstant('{autopf}') + '\sinT';
  if DataDirPage.Values[1] = '' then
     DataDirPage.Values[1] := 'C:\VST3';
  Result := True;
end;

// Returns selected DataDir
function GetDir(Param: String): String;
begin
  Result := DataDirPage.Values[StrToInt(Param)];
end;