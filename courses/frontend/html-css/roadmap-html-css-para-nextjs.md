# Roadmap HTML & CSS — Base para Next.js

> Objetivo: dominar o suficiente de HTML e CSS para não travar ao escrever JSX e estilizar componentes em Next.js. JavaScript/React vêm depois.

---

## 1. HTML — Estrutura e Semântica

### 1.1 Fundamentos obrigatórios
- Estrutura base de um documento (`<!DOCTYPE html>`, `<html>`, `<head>`, `<body>`)
- Tags de texto: `<h1>`–`<h6>`, `<p>`, `<span>`, `<strong>`, `<em>`
- Listas: `<ul>`, `<ol>`, `<li>`
- Links e navegação: `<a href="">`, atributos `target`, `rel`
- Imagens: `<img src="" alt="">` — **o `alt` é obrigatório**
- Divisões de layout: `<div>`, `<section>`, `<article>`, `<header>`, `<footer>`, `<main>`, `<nav>`, `<aside>`

### 1.2 Formulários (muito usados em Next.js)
- `<form>`, `<input>`, `<textarea>`, `<select>`, `<button>`
- Atributos: `type`, `name`, `id`, `placeholder`, `value`, `required`, `disabled`
- Label associado: `<label for="id">`
- Diferença entre `<button type="submit">` e `<button type="button">`

### 1.3 Semântica HTML5 (importante para acessibilidade e SEO)
- Usar as tags certas para o conteúdo certo (`<nav>` para menus, `<main>` para conteúdo principal, etc.)
- Atributos de acessibilidade: `aria-label`, `role`
- `<meta>` tags no `<head>` (charset, viewport, description)

### 1.4 Atributos globais essenciais
- `id`, `class`, `style`, `data-*`
- Em JSX esses viram `className` e `htmlFor` — anote isso para quando chegar no Next

---

## 2. CSS — Estilização

### 2.1 Como o CSS funciona
- Seletores: elemento (`p`), classe (`.classe`), id (`#id`), atributo (`[type="text"]`)
- Cascata e especificidade — por que uma regra sobrescreve a outra
- Herança de propriedades
- Três formas de aplicar CSS: externo (arquivo `.css`), interno (`<style>`), inline (`style=""`)
  - No Next.js usa-se CSS Modules ou Tailwind — mas o conceito é o mesmo

### 2.2 Box Model (fundamental — tudo em CSS é uma caixa)
```
┌──────────────────────────────┐
│           margin             │
│  ┌────────────────────────┐  │
│  │        border          │  │
│  │  ┌──────────────────┐  │  │
│  │  │     padding      │  │  │
│  │  │  ┌────────────┐  │  │  │
│  │  │  │  content   │  │  │  │
│  │  │  └────────────┘  │  │  │
│  │  └──────────────────┘  │  │
│  └────────────────────────┘  │
└──────────────────────────────┘
```
- `width`, `height`, `padding`, `margin`, `border`
- `box-sizing: border-box` — use sempre, evita muita dor de cabeça

### 2.3 Display e posicionamento
- `display: block | inline | inline-block | none`
- `position: static | relative | absolute | fixed | sticky`
- `z-index` — controla qual elemento fica na frente
- `overflow: hidden | scroll | auto`

### 2.4 Flexbox (essencial — layout mais usado em componentes React/Next)
- Container: `display: flex`, `flex-direction`, `justify-content`, `align-items`, `gap`, `flex-wrap`
- Filho: `flex`, `flex-grow`, `flex-shrink`, `flex-basis`, `align-self`, `order`

```css
/* Padrão clássico: centralizar qualquer coisa */
.container {
  display: flex;
  justify-content: center;
  align-items: center;
}
```

### 2.5 Grid (muito usado para layouts de página em Next.js)
- Container: `display: grid`, `grid-template-columns`, `grid-template-rows`, `gap`
- Filho: `grid-column`, `grid-row`
- Atalho útil: `grid-template-columns: repeat(3, 1fr)`

### 2.6 Tipografia
- `font-family`, `font-size`, `font-weight`, `line-height`, `letter-spacing`
- `text-align`, `text-decoration`, `text-transform`
- Unidades: `px`, `rem`, `em`, `%` — prefira `rem` para fontes

### 2.7 Cores e fundos
- `color`, `background-color`, `background-image`, `background-size`, `background-position`
- Formatos de cor: `#hex`, `rgb()`, `hsl()`, variáveis CSS (`--cor-primaria`)
- `opacity`, `rgba()` para transparência

### 2.8 Responsividade (indispensável para Next.js)
- Media queries: `@media (max-width: 768px) { ... }`
- Unidades relativas: `%`, `vw`, `vh`, `rem`
- Mobile-first: escrever o CSS base para mobile e expandir com `min-width`
- `min-width`, `max-width` em containers

### 2.9 Variáveis CSS (muito usado com design systems)
```css
:root {
  --cor-primaria: #3b82f6;
  --espacamento-base: 1rem;
}

.botao {
  background-color: var(--cor-primaria);
  padding: var(--espacamento-base);
}
```

### 2.10 Pseudo-classes e pseudo-elementos
- `:hover`, `:focus`, `:active`, `:disabled`, `:nth-child()`
- `::before`, `::after`, `::placeholder`

### 2.11 Transições e animações básicas
- `transition: property duration ease`
- `transform: translateX() | translateY() | scale() | rotate()`
- `animation` + `@keyframes` (básico — saber que existe)

---

## 3. O que é diferente no Next.js (anote para não se confundir)

| HTML/CSS puro | Next.js / JSX |
|---|---|
| `class=""` | `className=""` |
| `for=""` no label | `htmlFor=""` |
| `<img>` normal | `<Image>` do `next/image` |
| `<a href="">` | `<Link href="">` do `next/link` |
| CSS global | CSS Modules (`.module.css`) ou Tailwind |
| Inline style com string | Inline style com objeto: `style={{ color: 'red' }}` |

---

## 4. Ordem de estudo sugerida

1. [x] Estrutura HTML e tags básicas
2. [x] Formulários
3. [ ] Box model + display
4. [ ] Flexbox (pratique até decorar)
5. [ ] CSS Grid
6. [ ] Responsividade com media queries
7. [ ] Variáveis CSS e pseudo-classes
8. [ ] Construir 2–3 layouts completos do zero (header, main, footer, cards)
9. [ ] Replicar uma página simples que você já conhece (ex: página de login)
10. [ ] Partir para JavaScript

---

## 5. Recursos

- [MDN Web Docs — HTML](https://developer.mozilla.org/pt-BR/docs/Web/HTML) — referência definitiva
- [MDN Web Docs — CSS](https://developer.mozilla.org/pt-BR/docs/Web/CSS)
- [Flexbox Froggy](https://flexboxfroggy.com/) — jogo para aprender Flexbox
- [CSS Grid Garden](https://cssgridgarden.com/) — jogo para aprender Grid
- [Can I Use](https://caniuse.com/) — verificar suporte de browsers

---

*Quando dominar esses tópicos, você vai conseguir ler e escrever JSX sem travar na parte de estrutura e estilo. O Next.js não exige nada além disso de HTML/CSS antes de começar.*
