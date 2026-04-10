#Bibliotecas utilizadas: pandas y matplotlib para generación de gráficos
import os

import matplotlib.pyplot as plt
import pandas as pd

INPUT_DIR = "data/measurements/"
OUTPUT_DIR = "data/plots/"
FILES = {
    "Naive": "naive_results.txt",
    "Strassen": "strassen_results.txt"
}

def load_and_process_data(filepath):
    if not os.path.exists(filepath):
        print(f"Advertencia: No se encontró {filepath}")
        return None
    
    df = pd.read_csv(filepath, sep=' ', header=None, names=['N', 'Tiempo', 'Memoria'])

    return df.groupby('N').mean().reset_index()

def generate_matrix_plots():
    all_data = {}
    for algo, filename in FILES.items():
        df = load_and_process_data(os.path.join(INPUT_DIR, filename))
        if df is not None:
            all_data[algo] = df

    if not all_data:
        print("Error: No hay datos para graficar matrices.")
        return
    
    if not os.path.exists(OUTPUT_DIR): os.makedirs(OUTPUT_DIR)

    plt.figure(figsize=(10, 6))
    for algo, df in all_data.items():
        plt.loglog(df['N'], df['Tiempo'], label=algo, marker='o', linewidth=2)
    
    plt.xlabel('Dimensión de la Matriz (N)')
    plt.ylabel('Tiempo de Ejecución (Segundos)')
    plt.title('Comparación Temporal: Multiplicación de Matrices- Escala Log')
    plt.grid(True, which="both", ls="--", alpha=0.7)
    plt.legend()
    plt.savefig(os.path.join(OUTPUT_DIR, "time_comparison_matrix.png"), dpi=300)
    print("¡Gráfico de TIEMPO de matrices guardado!")

    plt.figure(figsize=(10, 6))
    for algo, df in all_data.items():
        plt.plot(df['N'], df['Memoria'], label=algo, marker='s', linewidth=2)
    
    plt.xlabel('Dimensión de la Matriz (N)')
    plt.ylabel('Pico de Memoria RAM (KB)')
    plt.title('Consumo de Memoria: Multiplicación de Matrices')
    plt.xscale('log', base=2)
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend()
    
    plt.savefig(os.path.join(OUTPUT_DIR, "memory_comparison_matrix.png"), dpi=300)
    print("¡Gráfico de MEMORIA de matrices guardado!")

if __name__ == "__main__":
    generate_matrix_plots()