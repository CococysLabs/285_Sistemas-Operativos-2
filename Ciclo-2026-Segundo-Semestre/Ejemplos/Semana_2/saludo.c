#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/utsname.h>

static char *nombre = "SO2";
module_param(nombre, charp, 0444);
MODULE_PARM_DESC(nombre, "Nombre a saludar");

static int __init saludo_init(void)
{
    pr_info("saludo: Hola %s, kernel %s\n", nombre, utsname()->release);
    return 0;
}

static void __exit saludo_exit(void)
{
    pr_info("saludo: Adios %s\n", nombre);
}

module_init(saludo_init);
module_exit(saludo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laboratorio SO2");
MODULE_DESCRIPTION("Modulo de ejemplo con parametro");