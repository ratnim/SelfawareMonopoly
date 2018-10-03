\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{cgspaper}[03/23/2011 CGS Paper class by J.E. Kyprianidis; 10/14/2013 English variant by J. Truemper]

\newif\ifcgs@english

\DeclareOption{english}{%
    \cgs@englishtrue}

\DeclareOption{german}{%
	\cgs@englishfalse}

% Assume we're producing a german version unless the user explicitly specifies 'english' as package option
\ExecuteOptions{german}

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{acmsiggraph}}
\ProcessOptions
\LoadClass{acmsiggraph}

\RequirePackage[scaled=.92]{helvet}
\RequirePackage[T1]{fontenc}
\RequirePackage{times}
\RequirePackage{graphicx}
\RequirePackage{parskip}
\RequirePackage[labelfont=bf,textfont=it]{caption}


\gdef\@subject{}
\def\subject#1{\gdef\@subject{#1}}

\renewcommand{\copyrightspace}{%
    \let\oldthefootnote=\thefootnote% save original footnote definition
    \renewcommand{\thefootnote}{}%
    \footnotetext[0]{
    \parbox{200pt}{\vspace{10pt}\tiny\sffamily
	\ifcgs@english
		\includegraphics{cgspaper_en}\\[1ex]%
	\else%
		\includegraphics{cgspaper}\\[1ex]%
	\fi%
    \ifx\@subject\@empty\else
        {\@subject}\\[1ex]
    \fi
    http://www.hpi3d.de
    }}
    \let\thefootnote=\oldthefootnote% restore original footnote definition
}
