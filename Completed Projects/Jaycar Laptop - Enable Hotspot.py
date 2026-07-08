import subprocess
import sys


POWERSHELL_SCRIPT = r"""
Add-Type -AssemblyName System.Runtime.WindowsRuntime

$asTaskGeneric = ([System.WindowsRuntimeSystemExtensions].GetMethods() |
    Where-Object {
        $_.Name -eq 'AsTask' -and
        $_.GetParameters().Count -eq 1 -and
        $_.GetParameters()[0].ParameterType.Name -eq 'IAsyncOperation`1'
    })[0]

function Await($WinRtTask, $ResultType) {
    $asTask = $asTaskGeneric.MakeGenericMethod($ResultType)
    $netTask = $asTask.Invoke($null, @($WinRtTask))
    $netTask.Wait(-1) | Out-Null
    return $netTask.Result
}

$connectionProfile = [Windows.Networking.Connectivity.NetworkInformation,Windows.Networking.Connectivity,ContentType=WindowsRuntime]::GetInternetConnectionProfile()

if ($null -eq $connectionProfile) {
    Write-Error "No active internet connection profile found."
    exit 1
}

$tetheringManager = [Windows.Networking.NetworkOperators.NetworkOperatorTetheringManager,Windows.Networking.NetworkOperators,ContentType=WindowsRuntime]::CreateFromConnectionProfile($connectionProfile)

$result = Await ($tetheringManager.StartTetheringAsync()) ([Windows.Networking.NetworkOperators.NetworkOperatorTetheringOperationResult])

Write-Output "Mobile hotspot result: $($result.Status)"
"""


def enable_hotspot():
    try:
        result = subprocess.run(
            [
                "powershell",
                "-NoProfile",
                "-ExecutionPolicy",
                "Bypass",
                "-Command",
                POWERSHELL_SCRIPT,
            ],
            capture_output=True,
            text=True,
            check=False,
        )

        if result.stdout:
            print(result.stdout.strip())

        if result.stderr:
            print(result.stderr.strip(), file=sys.stderr)

        if result.returncode != 0:
            print("Failed to enable hotspot.")
            return False

        return True

    except FileNotFoundError:
        print("PowerShell was not found. This script is intended for Windows.")
        return False


if __name__ == "__main__":
    enable_hotspot()
