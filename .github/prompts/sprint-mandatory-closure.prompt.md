---
description: "Run a mandatory sprint closure for ft_nmap: verify PDF coverage gaps before any bonus work."
name: "FT Nmap Sprint Mandatory Closure"
argument-hint: "Sprint scope, changed files, and open blockers"
agent: "FT Nmap Plan Keeper"
---
Run a strict mandatory sprint closure for ft_nmap.

Use [ft_nmap.pdf](../../ft_nmap.pdf) as source of truth and treat bonus as blocked until mandatory is complete and stable.

Inputs:
- Sprint scope: {{input}}
- Current roadmap: [src/engine/ROADMAP_ENGINE.md](../../src/engine/ROADMAP_ENGINE.md)
- Team split: ENGINE (Persona B), NETWORK (Persona A)

Required workflow:
1. List mandatory PDF requirements and mark each as: Done / Partial / Missing / Unverified.
2. Map each changed file to one or more mandatory requirements, or flag as out-of-scope.
3. Identify blocking gaps that prevent mandatory completion.
4. Output exactly one next highest-priority action with owner (ENGINE or NETWORK).
5. If any mandatory item is not Done, explicitly return: BONUS BLOCKED.

Output format:
- Mandatory Coverage Table
- Out-of-Scope Findings
- Blocking Gaps
- Next Action (single)
- Bonus Gate (OPEN or BLOCKED)
