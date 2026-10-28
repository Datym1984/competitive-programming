import contextlib
import importlib.util
import io
import json
from pathlib import Path
import subprocess
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("teambook_build", Path(__file__).resolve().parents[1] / "build.py")
build = importlib.util.module_from_spec(spec)
spec.loader.exec_module(build)


class BuildTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.template = self.root / "teambook"
        self.template.mkdir()
        self.output = self.root / "build" / "teambook"
        for name in ("main.tex", "preamble.tex"):
            (self.template / name).write_text("% template\n", encoding="utf-8")
        self.section = self.root / "algorithms"
        self.section.mkdir()
        self.config = {"title": "A&B_#%", "subtitle": "Тимбук", "sections": [
            {"directory": "algorithms", "title": "Алгоритмы"},
        ]}
        self.write_config()
        for name, value in (("ROOT", self.root), ("TEMPLATE", self.template), ("BUILD", self.output)):
            patcher = patch.object(build, name, value)
            patcher.start()
            self.addCleanup(patcher.stop)

    def write_config(self):
        (self.template / "config.json").write_text(json.dumps(self.config), encoding="utf-8")

    def generate(self):
        with contextlib.redirect_stdout(io.StringIO()), patch.object(build, "revision", return_value="test"):
            build.generate()
        return json.loads((self.output / "manifest.json").read_text(encoding="utf-8"))

    def test_sources_are_complete_sorted_and_unchanged(self):
        (self.section / "z.cpp").write_text("int z;\n", encoding="utf-8")
        source = self.section / "A & B's_%.cpp"
        source.write_text("// Русский комментарий\nint x = 1;\n", encoding="utf-8")
        (self.section / "nested").mkdir()
        (self.section / "nested" / "code.hpp").write_text("int y;\n", encoding="utf-8")
        (self.section / "ignore.pdf").write_bytes(b"not a source")
        original = source.read_bytes()
        manifest = self.generate()
        self.assertEqual([p["source"] for p in manifest], [
            "algorithms/A & B's_%.cpp", "algorithms/nested/code.hpp", "algorithms/z.cpp",
        ])
        self.assertEqual((self.output / manifest[0]["listing"]).read_bytes(), original)
        self.assertEqual(source.read_bytes(), original)
        contents = (self.output / "contents.tex").read_text(encoding="utf-8")
        self.assertIn(r"A \& B's\_\%", contents)
        self.assertIn(r"\section{Алгоритмы}", contents)
        before = contents
        self.generate()
        self.assertEqual((self.output / "contents.tex").read_text(encoding="utf-8"), before)
        (self.section / "new.cpp").write_text("int new_file;", encoding="utf-8")
        self.assertEqual(len(self.generate()), 4)

    def test_missing_section_fails(self):
        self.config["sections"][0]["directory"] = "missing"
        self.write_config()
        with self.assertRaisesRegex(ValueError, "Invalid section"):
            self.generate()

    def test_duplicate_source_fails(self):
        (self.section / "a.cpp").write_text("int a;", encoding="utf-8")
        self.config["sections"] *= 2
        self.write_config()
        with self.assertRaisesRegex(ValueError, "included twice"):
            self.generate()

    def test_compiler_failure_is_reported_and_logged(self):
        self.output.mkdir(parents=True)
        result = subprocess.CompletedProcess([], 1, "compile error")
        with patch.object(build.subprocess, "run", return_value=result), contextlib.redirect_stderr(io.StringIO()):
            with self.assertRaisesRegex(ValueError, "LaTeX failed"):
                build.compile_pdf("tectonic", "tectonic")
        self.assertIn("compile error", (self.output / "build.log").read_text(encoding="utf-8"))

    def test_no_compiler_has_actionable_error(self):
        with patch.object(build.shutil, "which", return_value=None):
            with self.assertRaisesRegex(ValueError, "--generate-only"):
                build.find_engine("auto")


if __name__ == "__main__":
    unittest.main()
