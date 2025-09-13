# Testing de Software en Sistemas Embebidos - CESE - UBA

Este repositorio contiene el trabajo práctico 3 de la materia **Testing de Software en Sistemas Embebidos**.

## Autor
Lic. Mariano Ariel Deville

## Trabajo Práctico 3 – Testing Unitario

## Descripción
Seleccionar una biblioteca (o componente) del software a desarrollar en el TP final de la carrera de especialización / maestría y escribir un test unitario con ceedling que incluya por lo menos 5 test cases. El archivo de test debe tener por lo menos 65 líneas de extensión.

Se debe mantener bajo control de versión el código generado.

## Entrega
Repositorio con el archivo con las pruebas unitarias y el código de producción bajo prueba (preferentemente en bitbucket o github).

---

## Estructura del Repositorio
```
/mrf24drv
│
├── /src
│   └── drv_MRF24J40.c
│
├── /include
│   ├── app_delay_unlock.h
│   ├── compatibility.h
│   ├── drv_MRF24J40.h
│   ├── drv_MRF24J40_port.h
│   └── inc/drv_MRF24J40_registers.h
│
├── /test
│   ├── /support
│   │
│   └── test_mrf24j40.c
│
├── .clang-format
├── .gitignore
├── .pre-commit-config.yaml
├── doxyfile
├── project.yml
└── README.md
```
---

## Notas finales
- El código de producción está destinado a correr en un microcontrolador ARM.
- Alguna funciones que en producción son privadas se hicieron públicas para testearlas.
