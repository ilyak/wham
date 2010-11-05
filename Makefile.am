SUBDIRS = src tests

dist-hook:
	if test -d "$(srcdir)/.git" && type git > /dev/null 2>&1; then \
		( cd "$(srcdir)" && git log ) \
			> "$(distdir)/ChangeLog"; \
	fi
