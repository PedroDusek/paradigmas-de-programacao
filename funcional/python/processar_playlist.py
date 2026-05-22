
MUSICAS = (
    {"id": 1, "titulo": "Espresso",        "artista": "Sabrina Carpenter",      "genero": "pop",       "bpm": 117, "avaliacoes": [5, 4, 5, 3, 5]},
    {"id": 2, "titulo": "Cruel Summer",   "artista": "Taylor Swift",     "genero": "pop",       "bpm": 170, "avaliacoes": [5, 5, 4, 5, 5]},
    {"id": 3, "titulo": "As It Was",      "artista": "Harry Styles",     "genero": "pop",       "bpm": 174, "avaliacoes": [4, 5, 4, 4, 3]},
    {"id": 4, "titulo": "Dress",      "artista": "Taylor Swift",     "genero": "pop",       "bpm": 97,  "avaliacoes": [5, 4, 3, 5, 4]},
    {"id": 5, "titulo": "Levitating",     "artista": "Dua Lipa",         "genero": "pop",       "bpm": 103, "avaliacoes": [4, 3, 4, 5, 4]},
    {"id": 6, "titulo": "Blinding Lights","artista": "The Weeknd",       "genero": "synth-pop", "bpm": 171, "avaliacoes": [5, 5, 5, 4, 5]},
    {"id": 7, "titulo": "Save Your Tears","artista": "The Weeknd",       "genero": "synth-pop", "bpm": 118, "avaliacoes": [4, 4, 5, 3, 4]},
    {"id": 8, "titulo": "Montero",        "artista": "Lil Nas X",        "genero": "hip-hop",   "bpm": 179, "avaliacoes": [4, 5, 4, 4, 3]},
    {"id": 9, "titulo": "My Man on Willpower",     "artista": "Sabrina Carpenter",            "genero": "pop",      "bpm": 130,  "avaliacoes": [5, 5, 5, 5, 4]},
    {"id":10, "titulo": "Easy On Me",    "artista": "Adele",    "genero": "soul",       "bpm": 58, "avaliacoes": [3, 4, 3, 3, 4]},
    {"id":11, "titulo": "Industry Baby",  "artista": "Lil Nas X",        "genero": "hip-hop",   "bpm": 186, "avaliacoes": [4, 4, 5, 3, 4]},
    {"id":12, "titulo": "positions",      "artista": "Ariana Grande",    "genero": "r&b",       "bpm": 144, "avaliacoes": [4, 5, 4, 4, 5]},
    {"id":13, "titulo": "deja vu",       "artista": "Olivia Rodrigo",   "genero": "pop-punk",  "bpm": 166, "avaliacoes": [5, 4, 4, 5, 5]},
    {"id":14, "titulo": "drivers license","artista": "Olivia Rodrigo",   "genero": "pop",       "bpm": 75,  "avaliacoes": [5, 5, 5, 4, 5]},
    {"id":15, "titulo": "Cardigan",     "artista": "Taylor Swift",    "genero": "indie-pop", "bpm": 80,  "avaliacoes": [4, 5, 4, 3, 4]},
)



def calcular_media_avaliacoes(lista_de_notas):
    if len(lista_de_notas) == 0:
        return 0.0
    soma_total = sum(lista_de_notas)
    quantidade = len(lista_de_notas)
    return round(soma_total / quantidade, 2)


def adicionar_media_a_musica(musica):
    
    media_calculada = calcular_media_avaliacoes(musica["avaliacoes"])
    musica_com_media = {**musica, "media": media_calculada}
    return musica_com_media


def preparar_catalogo(catalogo):
    catalogo_com_medias = list(map(adicionar_media_a_musica, catalogo))
    return catalogo_com_medias





def filtrar_por_genero(catalogo, genero_escolhido):
    pertence_ao_genero = lambda musica: musica["genero"].lower() == genero_escolhido.lower()
    musicas_filtradas = list(filter(pertence_ao_genero, catalogo))
    return musicas_filtradas


def filtrar_por_nota_minima(catalogo, nota_minima):
    tem_nota_suficiente = lambda musica: musica["media"] >= nota_minima
    musicas_bem_avaliadas = list(filter(tem_nota_suficiente, catalogo))
    return musicas_bem_avaliadas


def filtrar_por_bpm(catalogo, bpm_minimo, bpm_maximo):
    esta_no_intervalo = lambda musica: bpm_minimo <= musica["bpm"] <= bpm_maximo
    musicas_no_ritmo = list(filter(esta_no_intervalo, catalogo))
    return musicas_no_ritmo






def ordenar_por_media(catalogo, do_maior_para_menor=True):
    catalogo_ordenado = sorted(
        catalogo,
        key=lambda musica: musica["media"],
        reverse=do_maior_para_menor
    )
    return catalogo_ordenado


def ordenar_por_bpm(catalogo, do_maior_para_menor=False):
    catalogo_ordenado = sorted(
        catalogo,
        key=lambda musica: musica["bpm"],
        reverse=do_maior_para_menor
    )
    return catalogo_ordenado






def sugerir_playlist_top_hits(catalogo, quantidade=5):
    catalogo_ordenado = ordenar_por_media(catalogo, do_maior_para_menor=True)
    top_hits = catalogo_ordenado[:quantidade]
    return top_hits


def sugerir_playlist_para_treino(catalogo, quantidade=5):
    musicas_animadas = filtrar_por_bpm(catalogo, bpm_minimo=130, bpm_maximo=250)
    musicas_bem_avaliadas = filtrar_por_nota_minima(musicas_animadas, nota_minima=3.8)
    playlist_treino = ordenar_por_media(musicas_bem_avaliadas, do_maior_para_menor=True)
    return playlist_treino[:quantidade]


def sugerir_playlist_para_relaxar(catalogo, quantidade=5):
    musicas_lentas = filtrar_por_bpm(catalogo, bpm_minimo=50, bpm_maximo=120)
    musicas_bem_avaliadas = filtrar_por_nota_minima(musicas_lentas, nota_minima=3.5)
    playlist_relaxamento = ordenar_por_media(musicas_bem_avaliadas, do_maior_para_menor=True)
    return playlist_relaxamento[:quantidade]


def sugerir_playlist_por_genero(catalogo, genero, quantidade=5):
    musicas_do_genero = filtrar_por_genero(catalogo, genero)
    playlist_genero = ordenar_por_media(musicas_do_genero, do_maior_para_menor=True)
    return playlist_genero[:quantidade]






def exibir_musicas(lista_de_musicas, titulo_da_secao=""):
    if titulo_da_secao:
        print(f"\n{'='*55}")
        print(f"  {titulo_da_secao}")
        print(f"{'='*55}")

    if len(lista_de_musicas) == 0:
        print("  Nenhuma música encontrada com esses critérios.")
        return

    for posicao, musica in enumerate(lista_de_musicas, start=1):
        print(f"  {posicao}. {musica['titulo']:<22} | {musica['artista']:<18} | {musica['genero']:<10} | BPM: {musica['bpm']:>3} | ({musica['media']})")


def exibir_generos_disponiveis(catalogo):
    todos_os_generos = list(map(lambda musica: musica["genero"], catalogo))
    generos_unicos = sorted(set(todos_os_generos))
    print("\n  Gêneros disponíveis:", " | ".join(generos_unicos))






def exibir_menu():
    print("\n" + "="*55)
    print("      GERENCIADOR DE PLAYLIST ")
    print("  Vem ouvir as melhores músicas <3 !!!         ")
    print("="*55)
    print("  1 - Ver catálogo completo")
    print("  2 - Sugestão: Top Hits (mais bem avaliadas)")
    print("  3 - Sugestão: Playlist para Treino")
    print("  4 - Sugestão: Playlist para Relaxar")
    print("  5 - Filtrar por gênero")
    print("  6 - Filtrar por nota mínima")
    print("  0 - Sair")
    print("-"*55)


def main():
    catalogo = preparar_catalogo(MUSICAS)

    print("\n  Catálogo carregado com", len(catalogo), "músicas.")
    exibir_generos_disponiveis(catalogo)

    rodando = True
    while rodando:
        exibir_menu()
        opcao = input("  Escolha uma opção: ").strip()

        if opcao == "1":
            exibir_musicas(catalogo, "CATÁLOGO COMPLETO")

        elif opcao == "2":
            playlist = sugerir_playlist_top_hits(catalogo, quantidade=5)
            exibir_musicas(playlist, "TOP HITS - As 5 mais bem avaliadas")

        elif opcao == "3":
            playlist = sugerir_playlist_para_treino(catalogo, quantidade=5)
            exibir_musicas(playlist, "PLAYLIST TREINO - Ritmo alto e bem avaliadas")

        elif opcao == "4":
            playlist = sugerir_playlist_para_relaxar(catalogo, quantidade=5)
            exibir_musicas(playlist, "PLAYLIST RELAXAMENTO - Ritmo calmo e bem avaliadas")

        elif opcao == "5":
            exibir_generos_disponiveis(catalogo)
            genero_digitado = input("\n  Digite o gênero desejado: ").strip()
            playlist = sugerir_playlist_por_genero(catalogo, genero_digitado)
            exibir_musicas(playlist, f"GÊNERO: {genero_digitado.upper()}")

        elif opcao == "6":
            try:
                nota = float(input("  Nota mínima (1 a 5): ").strip())
                playlist = filtrar_por_nota_minima(catalogo, nota)
                playlist = ordenar_por_media(playlist, do_maior_para_menor=True)
                exibir_musicas(playlist, f"MÚSICAS COM NOTA ≥ {nota}")
            except ValueError:
                print("  Por favor, digite um número válido.")


        elif opcao == "0":
            print("\n  Até logo! Volte para o mundo da arte musical em breve! \n")
            rodando = False

        else:
            print("  Opção inválida. Tente novamente.")



if __name__ == "__main__":
    main()