---
description: "Use when editing network scan code in ft_nmap. Require minimum test criteria per scan type before merge."
name: "FT Nmap Network Scan Test Criteria"
applyTo: "src/network/**"
---
# Network Scan Criteria (Mandatory)

This instruction applies to NETWORK-only work: packet send/capture, timeout handling, and scan-state classification.

## Ownership Guard
- NETWORK owns implementation of SYN, NULL, ACK, FIN, XMAS, UDP scan behavior.
- ENGINE owns orchestration, formatting, and roadmap/reporting.
- Do not move formatting/business-report logic into network files.

## Mandatory Coverage Rules
For each commit in NETWORK, include at least one of:
- New mandatory scan type implemented, or
- Correctness fix for scan-state classification, or
- Robustness fix for timeout/error handling.

## Minimum Validation Per Scan Type
For each modified scan type, validate all four points:
- Probe path: packet creation/send path is exercised.
- Capture path: expected response is parsed from pcap capture.
- Timeout path: no response leads to deterministic fallback state.
- Error path: socket/pcap failures return controlled errors without crash.

## Classification Expectations (project-level)
- SYN: classify using SYN/ACK, RST, or timeout evidence.
- NULL/FIN/XMAS: classify using RST or no-response evidence.
- ACK: classify filtered vs unfiltered behavior from reply evidence.
- UDP: classify open/open|filtered/closed behavior from ICMP/timeout evidence.

## Threading and Limits
- Respect speedup range from ENGINE input: default 0, max 250.
- Avoid unbounded thread creation.
- Keep behavior deterministic under low and high thread counts.

## Required Commit Footer
Mandatory-Req: <mandatory PDF bullet(s) covered>
Owner: NETWORK
Scans-Touched: <SYN|NULL|ACK|FIN|XMAS|UDP>
Validation: <commands run + expected states>
