---
description: "Use when editing engine code in ft_nmap. Enforce mandatory-PDF checklist per commit and strict scope control."
name: "FT Nmap Engine Commit Checklist"
applyTo: "src/engine/**, src/main.c"
---
# Engine Commit Checklist (Mandatory First)

Use this checklist before finishing any commit that touches engine files.
If one item fails, the commit is not ready.

## Scope Guard
- Keep changes inside ENGINE concerns only: parse, orchestration, result aggregation, output formatting, timing, and error handling.
- Do not implement packet crafting/capture logic here (NETWORK ownership).
- If a task crosses boundaries, split into two tasks with explicit owner.

## Mandatory Mapping (PDF)
- State which mandatory requirement(s) this commit advances.
- If no mandatory item is advanced, postpone the change.
- Do not add bonus behavior while mandatory has open gaps.

## Pre-Commit Checklist (required)
- Requirement link: map this commit to at least one mandatory PDF bullet.
- Input handling: invalid arguments and invalid targets return clear errors without crashes.
- Limits: ports default to 1-1024, max scanned ports <= 1024.
- Scan selection: if scan is omitted, all mandatory scans are requested to NETWORK.
- Speedup bounds: default 0, max 250.
- Output contract: result lines stay clean/readable and include elapsed scan time context.
- Memory safety: no leaks, no double free, no null dereference on error paths.

## Commit Message Footer (required)
Add this footer block to each engine commit message:

Mandatory-Req: <list of PDF mandatory bullets covered>
Owner: ENGINE
Risk: <low|medium|high>
Validation: <exact command(s) and expected outcome>

## Handoff to NETWORK
When engine depends on network output, include:
- Requested data fields per port/scan.
- Expected state values and meaning.
- One concrete acceptance check to close the handoff.
