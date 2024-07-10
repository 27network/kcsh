# listing of interesting references

Variables internes bash: variables.c:545

backticks vs `$()`: https://www.baeldung.com/linux/command-substitution#syntax

---
APPLICATION USAGE (export utility) (useful for errexit)

Note that, unless X was previously marked readonly, the value of "$?" after:

export X=$(false)

will be 0 (because export successfully set X to the empty string) and that execution continues, even if set -e is in effect. In order to detect command substitution failures, a user must separate the assignment from the export, as in:

X=$(false)
export X



Tests:
- `echo <<EOF |||`
	- error then heredoc. what the fuck.
