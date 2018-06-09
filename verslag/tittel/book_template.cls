%% Latex template for VUB courses/thesis
%% Segers Laurent

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{book_template}[2017/05/17 Course template]

\DeclareOption{dutch}{\@dutchtrue \@englishfalse}
\DeclareOption{english}{\@dutchfalse \@englishtrue }
\newif\if@dutch
\newif\if@english
\@dutchfalse
\@englishtrue % default = english

\ProcessOptions\relax

\LoadClass[12pt,oneside]{book}
%%% 
%% load packages
\RequirePackage{blindtext}
\RequirePackage{xcolor}
\RequirePackage{algorithmic}
\RequirePackage{listings}
\RequirePackage{caption}
\RequirePackage[utf8]{inputenc}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{color}   %May be necessary if you want to color links
\RequirePackage{makeidx}
\RequirePackage{nomencl}
\RequirePackage{amsmath}
\RequirePackage{hyperref}
\RequirePackage[backend=biber,style=ieee,sorting=none,backref=true]{biblatex}
\RequirePackage{pdfpages}
\RequirePackage{titlesec}
\RequirePackage{tikz}
\RequirePackage{amssymb}
\RequirePackage[export]{adjustbox}
\RequirePackage{upquote}
\RequirePackage{vub}
\RequirePackage{setspace}
\RequirePackage{csquotes}
\if@english
	\RequirePackage[english]{babel} %\RequirePackage[dutch, english]{babel}
	\renewcommand\lstlistingname{\textbf{Snippet}}	
\fi
\if@dutch
    	\RequirePackage[dutch]{babel} %\RequirePackage[dutch, english]{babel}
	\renewcommand\lstlistingname{\textbf{Codefragment}}
	\DeclareFieldFormat [online] {url}{[Online] Beschikbaar: \url{#1}}
\fi
\usetikzlibrary{arrows,shapes,snakes,automata,backgrounds,petri}

%% define our colors
\definecolor{black}{rgb}{0,0,0}
\definecolor{darkgray}{rgb}{0.2,0.2,0.2}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{lightgray}{rgb}{0.8,0.8,0.8}
\definecolor{ultralightgray}{rgb}{0.95,0.95,0.95}
\definecolor{blue}{rgb}{0,0.2,1}
\definecolor{lightblue}{rgb}{0.2,0.6,1}
\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{mauve}{rgb}{0.58,0,0.82}

% define our latex commands %% syntax commands are always prepended by "syn" for syntax
\newcommand{\synterminal}[1]{\textcolor{blue}{\#: \textit{#1}}}
\newcommand{\filepath}[1]{\textcolor{darkgray}{$\hookrightarrow$\textit{#1}}}
\newcommand{\keyword}[1]{\textit{#1}}

%% setup color for links
\renewcommand\UrlFont{\color{blue}}
\hypersetup{
    colorlinks = true,
    citecolor=black,
    linktoc=all,     %set to all if you want both sections and subsections linked
    filecolor=black,
    linkcolor=black,
    urlcolor=blue
}

%% define the look and feel of code snippets 
\lstset{
  %frame=tb,  
  numbers=left,
  xleftmargin=7.5mm,
  framexleftmargin=4mm,
  aboveskip=3mm,
  belowskip=3mm,
  showstringspaces=false,
  columns=flexible,
  basicstyle={\small\ttfamily},  
  keywordstyle=\color{blue},
  commentstyle=\color{dkgreen},
  stringstyle=\color{mauve},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=3,  
  frame=l,
  framesep=4.5mm,
  framexleftmargin=2.5mm,
  fillcolor=\color{ultralightgray},
  rulecolor=\color{black},%lightblue},  
  numberstyle=\normalfont\tiny\color{black}  
}

\makeatletter
\def\blx@maxline{77}
\makeatother
% \DeclareFieldFormat [article] {journaltitle}{\textbf{\textit{#1\isdot}}}
\DeclareFieldFormat [online] {title}{\textit{#1}}
\captionsetup[lstlisting]{singlelinecheck=false, margin=0pt}
\DeclareCaptionFormat{listing}{\rule{\dimexpr\textwidth+17pt\relax}{0.4pt}}
% customize backref for biblatex
\DefineBibliographyStrings{english}{backrefpage = {cit. on p.}}% originally “cited on page” backrefpages = {},% originally “cited on pages”}
\DefineBibliographyStrings{dutch}{backrefpage = {cit. op p.}}% originally “cited on page”  backrefpages = {},% originally “cited on pages” }



\oddsidemargin=0mm
\evensidemargin=0mm

%% format of the different parts

\titlespacing{\chapter}{0cm}{0cm}{1cm}
\titleformat{\chapter}[hang]
    {\filright\bfseries\Huge\normalfont}
    {\Huge\thechapter\:\:}{0pt}{\sc}
    [\titlerule]
% These must be changed for double sided output !
\makeatother
\pagestyle{plain}
\textheight=230mm
\textwidth=170mm
\topmargin=0mm
\headheight=0mm
\headsep=0mm
\oddsidemargin=0mm
\evensidemargin=0mm