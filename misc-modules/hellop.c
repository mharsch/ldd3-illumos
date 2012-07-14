#include <sys/modctl.h>
#include <sys/conf.h>
#include <sys/devops.h>
#include <sys/cmn_err.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>

static int hello_attach(dev_info_t *dip, ddi_attach_cmd_t cmd);

static struct dev_ops qotd_dev_ops = {
	DEVO_REV,		/* devo_rev */
	0,			/* devo_refcnt */
	ddi_no_info,		/* devo_getinfo */
	nulldev,		/* devo_identify */
	nulldev,		/* devo_probe */
	hello_attach,		/* devo_attach */
	nulldev,		/* devo_detach */
	nodev,			/* devo_reset */
	(struct cb_ops *)NULL,	/* devo_cb_ops */
	(struct bus_ops *)NULL,	/* devo_bus_ops */
	nulldev			/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,
	"Hello World",
	&qotd_dev_ops
};

static struct modlinkage modlinkage = {
	MODREV_1,
	(void *)&modldrv,
	NULL
};

int
_init(void)
{
	return (mod_install(&modlinkage));
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

int
_fini(void)
{
	cmn_err(CE_NOTE, "Goodbye, cruel world\n");
	return (mod_remove(&modlinkage));
}

static int
hello_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int howmany = 0;
	char buf[128];
	char *whom = buf;

	switch (cmd) {
	case DDI_ATTACH:
		howmany = ddi_prop_get_int(DDI_DEV_T_ANY,
		    dip, DDI_PROP_DONTPASS, "howmany", 1);

		if (ddi_prop_lookup_string(DDI_DEV_T_ANY,
		    dip, DDI_PROP_DONTPASS, "whom", &whom) != DDI_SUCCESS) {
			strlcpy(whom, "world", sizeof("world"));
		}

		int i = 0;
		for (i = 0; i < howmany; i++) {
			cmn_err(CE_NOTE, "Hello, %s\n", whom);
		}
		return (DDI_SUCCESS);
	default:
		return (DDI_FAILURE);
	}
}
