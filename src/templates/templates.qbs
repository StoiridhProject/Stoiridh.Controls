////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//            Copyright (C) 2016 William McKIE                                                    //
//                                                                                                //
//            This program is free software: you can redistribute it and/or modify                //
//            it under the terms of the GNU General Public License as published by                //
//            the Free Software Foundation, either version 3 of the License, or                   //
//            (at your option) any later version.                                                 //
//                                                                                                //
//            This program is distributed in the hope that it will be useful,                     //
//            but WITHOUT ANY WARRANTY; without even the implied warranty of                      //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       //
//            GNU General Public License for more details.                                        //
//                                                                                                //
//            You should have received a copy of the GNU General Public License                   //
//            along with this program.  If not, see <http://www.gnu.org/licenses/>.               //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
import qbs 1.0
import qbs.File
import qbs.FileInfo
import Stoiridh.QtQuick

QtQuick.DynamicLibrary {
    name: "Stoiridh.Controls.Templates"
    targetName: "StoiridhControlsTemplates"
    type: ['stoiridh.controls.templates.hpp'].concat(base)
    installFileTagsFilter: ['dynamiclibrary']

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Dependencies                                                                              //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Depends {
        name: 'Qt'
        submodules: [
            'core-private',
            'gui-private',
            'qml-private',
            'quick-private'
        ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Configuration                                                                             //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    cpp.defines: [
        'STOIRIDH_CONTROLS_TEMPLATES_LIB',
        'QT_NO_CAST_FROM_ASCII',
        'QT_NO_CAST_TO_ASCII'
    ].concat(base)
    cpp.includePaths: [
        FileInfo.joinPaths(product.buildDirectory, 'include'),
        product.sourceDirectory,
    ].concat(base)

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Sources                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    files: [
        "control.cpp",
        "control.hpp",
        "global.hpp",
        "padding.cpp",
        "padding.hpp",
    ]

    Group {
        name: "Public Headers"
        fileTags: ['public.hpp']
        overrideTags: true
        prefix: 'api/public/'
        files: [
            "Control",
            "Padding",
        ]
    }

    Group {
        name: "Private Headers"
        fileTags: ['private.hpp']
        overrideTags: true
        prefix: 'api/private/'
        files: [
            "control_p.hpp",
        ]
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Exports                                                                                   //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Export {
        Depends { name: 'cpp' }

        cpp.defines: [
            'QT_NO_CAST_FROM_ASCII',
            'QT_NO_CAST_TO_ASCII'
        ]

        cpp.includePaths: [].concat(FileInfo.joinPaths(product.buildDirectory, 'include'))
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  Rules                                                                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    Rule {
        inputs: ['hpp', 'public.hpp', 'private.hpp']

        Artifact {
            fileTags: ['stoiridh.controls.templates.hpp']
            filePath: {
                var destinationPath = 'include/StoiridhControlsTemplates';
                var relativeFilePath = FileInfo.relativePath(product.sourceDirectory,
                                                             input.filePath);

                if (input.fileTags.indexOf('hpp') !== -1) {
                    destinationPath += '/Public';
                } else if (input.fileTags.indexOf('private.hpp') !== -1) {
                    destinationPath += '/Private';
                    relativeFilePath = relativeFilePath.replace('api/private', '');
                } else if (input.fileTags.indexOf('public.hpp') !== -1) {
                    relativeFilePath = relativeFilePath.replace('api/public', '');
                }

                return FileInfo.joinPaths(destinationPath, relativeFilePath);
            }
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = 'copying ' + input.fileName;
            cmd.highlight = 'filegen';
            cmd.silent = true;
            cmd.sourceCode = function() {
                File.copy(input.filePath, output.filePath);
            };
            return cmd;
        }
    }
}
