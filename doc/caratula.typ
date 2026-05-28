#let caratula(
  titulo: "",
  subtitulo: none,
  fecha: "",
  materia: "",
  submateria: none,
  grupo: none,
  integrantes: (), // Lista de pares ("Nombre", "LU", "Email")
  directores: (),   // Opcional
) = {
  set page(
    margin: (x: 2cm, y: 2cm),
    numbering: none,
  )
  set text(font: "libertinus serif", lang: "es")

  // Header
  align(right)[#image("./logo_dc.jpg", width: 45%)]

  v(10%)

  // --- TÍTULOS ---
  block(width: 100%)[
    #set align(left)
    #text(24pt, weight: "bold")[#titulo]
    
    #if subtitulo != none [
      #v(-10pt)
      #text(16pt, weight: "bold")[#subtitulo]
    ]
    
    #v(-5pt)
    #line(length: 100%, stroke: 1pt)
    
    #set text(size: 12pt)
    #grid(
      columns: (1fr, 1fr),
      fecha,
      align(right)[#materia]
    )
    #if submateria != none {
      align(right)[#submateria]
    }
  ]

  v(2em)

  // --- CUERPO (Integrantes) ---
  align(center)[
    #if grupo != none {
      text(weight: "bold")[#grupo]
      v(1em)
    }

    #table(
      columns: (35%, auto, 35%),
      align: (center, center, center),
      stroke: (x, y) => {
        let border = 0.5pt + black
        (
          top: { border },
          bottom: { border },
          left:   if x == 0 { border },
          right:  if x == 2 { border },
        )
      },
      row-gutter: 0.3em,
      table.header[Integrante][LU][Correo Eléctronico],
      ..integrantes.map(i => (i.at(0), i.at(1), i.at(2))).flatten()
    )

    #if directores.len() > 0 {
      v(1em)
      table(
        columns: (auto, auto),
        stroke: none,
        ..directores.map(d => (d.at(0), d.at(1))).flatten()
      )
    }
  ]

  v(1fr) // Empuja el footer hacia abajo

  // --- FOOTER (El bloque que tradujimos antes) ---
  grid(
    columns: (55%, 45%),
    align(left + top)[
      #image("./logo_uba.jpg", width: 70%)
    ],
    align(right + bottom)[
      #set text(size: 9pt)
      *Facultad de Ciencias Exactas y Naturales* \
      Universidad de Buenos Aires \
      #v(-2pt)
      #set text(size: 7pt)
      Ciudad Universitaria - Pabellón I \
      Intendente Güiraldes 2160 - C1428EGA \
      Ciudad Autónoma de Buenos Aires - Argentina \
      Tel/Fax: (54 11) 4576-3359 \
      #link("http://exactas.uba.ar")
    ]
  )
  
  pagebreak()
}

