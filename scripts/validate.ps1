
$ErrorActionPreference = "Stop"

$projectRoot = Split-Path -Parent $PSScriptRoot
Set-Location $projectRoot

function Invoke-Checked {
    param(
        [string]$Name,
        [string]$Command,
        [string[]]$Arguments
    )

    Write-Host "`n===== $Name =====" -ForegroundColor Cyan

    & $Command @Arguments

    if ($LASTEXITCODE -ne 0) {
        throw "$Name failed (Exit Code: $LASTEXITCODE)"
    }
}

try {
    Invoke-Checked "Debug Configure" "cmake" @(
        "--preset", "windows-debug"
    )

    Invoke-Checked "Debug Build" "cmake" @(
        "--build", "--preset", "windows-debug"
    )

    Invoke-Checked "Debug Tests" "ctest" @(
        "--preset", "windows-debug",
        "--output-on-failure"
    )

    Invoke-Checked "Release Configure" "cmake" @(
        "--preset", "windows-release"
    )

    Invoke-Checked "Release Build" "cmake" @(
        "--build", "--preset", "windows-release"
    )

    Invoke-Checked "Release Tests" "ctest" @(
        "--preset", "windows-release",
        "--output-on-failure"
    )

    Write-Host "`nM0 VALIDATION PASSED" -ForegroundColor Green
    exit 0
}
catch {
    Write-Error $_
    exit 1
}
